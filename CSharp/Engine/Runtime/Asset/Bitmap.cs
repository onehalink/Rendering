using System;
using System.IO;


namespace Engine
{
    public enum BitmapFormat
    {
        B8G8R8,
        B8G8R8A8,
    }


    /// <summary>
    /// Encode/Decode uncompressed 24-bit(B8G8R8) or 32-bit(B8G8R8A8) *.bmp file
    /// </summary>
    public class Bitmap
    {
        public const int FileHeaderSize		= 14;
        public const int InfoHeaderSize		= 40;
        public const int DefaultBitsOffset	= FileHeaderSize + InfoHeaderSize;


        public int Width { get; private set; }
        public int Height { get; private set; }
        public byte[] Buffer { get; private set; }
        public BitmapFormat Format { get; private set; }
        public int ChannelCount { get; private set; }


        public Bitmap(int width, int height, BitmapFormat format)
        {
            int channelCount = format == BitmapFormat.B8G8R8 ? 3 : 4;

            Width			= width;
            Height			= height;
            Buffer			= new byte[ channelCount * width * height ];
            Format			= format;
            ChannelCount	= channelCount;
        }


        /// <summary>
        /// The pixel's high 8-bit is unused if Format == BitmapFormat.B8G8R8
        /// </summary>
        public void SetPixel(int x, int y, uint pixel)
        {
            for ( int index = 0; index < ChannelCount; index++ )
                Buffer[ ChannelCount * ( Width * y + x ) + index ] = (byte)( ( pixel >> ( 8 * index ) ) & 0xFF );
        }

        public uint GetPixel(int x, int y)
        {
            uint ret = 0;
            for ( int index = 0; index < ChannelCount; index++ )
                ret |= (uint)( Buffer[ ChannelCount * ( Width * y + x ) + index ] << ( 8 * index ) );

            return ret;
        }

        public void FlipHorizontal()
        {
            var Fn = (ref byte a, ref byte b) =>
            {
                byte temporary	= a;
                a				= b;
                b				= temporary;
            };

            int halfWidth = Width / 2;
            for ( int y = 0; y < Height; y++ )
                for ( int x = 0; x < halfWidth; x++ )
                    for ( int index = 0; index < ChannelCount; index++ )
                        Fn(
                            ref Buffer[ ChannelCount * ( Width * y + x ) + index ],
                            ref Buffer[ ChannelCount * ( Width * y + ( Width - 1 - x ) ) + index ]
                            );
        }

        public void FlipVertical()
        {
            var Fn = (ref byte a, ref byte b) =>
            {
                byte temporary	= a;
                a				= b;
                b				= temporary;
            };

            int halfHeight = Height / 2;
            for ( int y = 0; y < halfHeight; y++ )
                for ( int x = 0; x < Width; x++ )
                    for ( int i = 0; i < ChannelCount; i++ )
                        Fn(
                            ref Buffer[ ChannelCount * ( Width * y + x ) + i ],
                            ref Buffer[ ChannelCount * ( Width * ( Height - 1 - y ) + x ) + i ]
                            );
        }


        /// <summary>
        /// Test if buffer is a valid *.bmp file representation
        /// </summary>
        public static bool IsValid(byte[] buffer)
        {
            if ( buffer.Length < DefaultBitsOffset )
                return false;

            if ( buffer[0] != 'B' || buffer[1] != 'M' )
                return false;

            int bitCount = BitConverter.ToInt32(buffer, 28);
            if ( bitCount != 24 && bitCount != 32 )
                return false;

            return true;
        }

        public static byte[] Encode(Bitmap instance)
        {
            int imageSize = instance.ChannelCount * instance.Width * instance.Height;
            int byteCount = DefaultBitsOffset + imageSize;

            using( var ms = new MemoryStream(byteCount) )
            using ( var writer = new BinaryWriter(ms) )
            {
                // set Bitmap FileHeader
                writer.Write( "BM".ToCharArray() );
                writer.Write(byteCount);
                writer.Write(0);
                writer.Write(DefaultBitsOffset);

                // set Bitmap InfoHeader
                writer.Write(InfoHeaderSize);
                writer.Write( instance.Width );
                writer.Write( instance.Height );
                writer.Write( (short)1 );
                writer.Write( (short)( 8 * instance.ChannelCount ) );
                writer.Write(0);
                writer.Write(imageSize);
                writer.Write(0);
                writer.Write(0);
                writer.Write(0);
                writer.Write(0);

                // set image data
                writer.Write( instance.Buffer );

                return ms.ToArray();
            }
        }

        public static Bitmap Decode(byte[] buffer)
        {
            int offset = BitConverter.ToInt32(buffer, 10);

            int width			= BitConverter.ToInt32(buffer, 18);
            int height			= BitConverter.ToInt32(buffer, 22);
            int bitCount		= BitConverter.ToInt32(buffer, 28);
            BitmapFormat format	= bitCount == 24 ? BitmapFormat.B8G8R8 : BitmapFormat.B8G8R8A8;

            var ret = new Bitmap(width, height, format);

            for ( int index = 0; index < ret.Buffer.Length; index++ )
                ret.Buffer[index] = buffer[ offset + index ];

            return ret;
        }
    }
}
