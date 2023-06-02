using System;
using System.IO;
using System.Runtime.InteropServices;



namespace Engine
{
	public enum WaveFormatTag
	{
		PCM		= 1,
		Float	= 3,
	}


	/*
	public struct WaveRIFFHeader
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public Byte[]	ID;     // Must be "RIFF"
		public UInt32	size;	// The value should be the file size(*.wav file) - 8
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public Byte[]	format;	// Must be "WAVE"
	}


	public struct WaveFormatBlock
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public Byte[] ID;		// Must be "fmt "
		public UInt32 size;		// The value should be sizeof(FormatBlock) - 8
		public UInt16 formatTag;
		public UInt16 channelCount;
		public UInt32 samplesPerSecond;
		public UInt32 averageBytesPerSecond;
		public UInt16 blockAlign;
		public UInt16 bitsPerSample;
	}


	struct WaveDataBlock
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public Byte[] ID;	// Must be "data"
		public UInt32 size;	// Indicate the size in bytes of audio track
	}
	*/


	public class Wave
	{
		const int RIFFHeaderSize			= 12;
		const int FormatBlockSize			= 24;
		const int DataBlockSize				= 8;
		const int DefaultAudioTrackOffset	= RIFFHeaderSize + FormatBlockSize + DataBlockSize;


		public byte[] Buffer { get; private set; }
		public WaveFormatTag FormatTag { get; private set; }
		public int ChannelCount { get; private set; }
		public int Depth { get; private set; }
		public int SamplesPerSecond { get; private set; }
		public int AudioFrameSize { get; private set; }


		public Wave(int byteCount, WaveFormatTag formatTag, int channelCount, int depth, int samplesPerSecond)
		{
			Buffer				= new byte[byteCount];
			FormatTag			= formatTag;
			ChannelCount		= channelCount;
			Depth				= depth;
			SamplesPerSecond	= samplesPerSecond;
			AudioFrameSize		= depth / 8 * channelCount;
		}


		public static Wave Decode(byte[] buffer)
		{
			var formatTag			= (WaveFormatTag)BitConverter.ToInt16(buffer, 20);
			var channelCount		= BitConverter.ToInt16(buffer, 22);
			var samplesPerSecond	= BitConverter.ToInt32(buffer, 24);
			var depth				= BitConverter.ToInt16(buffer, 34);

			var size = BitConverter.ToInt32( buffer, DefaultAudioTrackOffset - 4 );

			var ret = new Wave(size, formatTag, channelCount, depth, samplesPerSecond);

			for( int index = 0; index < size; index++ )
				ret.Buffer[index] = buffer[ DefaultAudioTrackOffset + index ];

			return ret;

			/*
			unsafe
			{
				fixed (byte* pBuffer = buffer)
				{
					var dataPointer = new IntPtr(pBuffer);
					int offset		= 0;

					offset		+= RIFFHeaderSize;
					var format	= (WaveFormatBlock*)IntPtr.Add(dataPointer, offset);

					offset				+= FormatBlockSize;
					WaveDataBlock* data	= null;
					while( offset + DataBlockSize < buffer.Length )
					{
						data = (WaveDataBlock*)IntPtr.Add(dataPointer, offset);

						for( int index = 0; index < 4; index++ )
							if ( data->ID[index] != "data"[index] )
							{
								offset += DataBlockSize + (int)data->size;
								continue;
							}

						break;
					}

					Wave ret = new Wave( (int)data->size, (WaveFormatTag)format->formatTag, format->channelCount, format->bitsPerSample, (int)format->samplesPerSecond );
					fixed( void* to = ret.Buffer )
					{
						Memory.Copy(
							(void*)IntPtr.Add( new IntPtr(data), DataBlockSize ),
							to,
							(int)data->size
							);
					}

					return ret;
				}
			}
			*/
		}

		public static byte[] Encode(Wave instance)
		{
			int byteCount = DefaultAudioTrackOffset + instance.Buffer.Length;

			using ( var ms = new MemoryStream(byteCount) )
			using( var writer = new BinaryWriter(ms) )
			{
				// set RIFFHeader
				writer.Write( "RIFF".ToCharArray() );
				writer.Write( byteCount - 8 );
				writer.Write( "WAVE".ToCharArray() );

				// set FormatBlock
				writer.Write( "fmt ".ToCharArray() );
				writer.Write( FormatBlockSize - 8 );
				writer.Write( (ushort)instance.FormatTag );
				writer.Write( (ushort)instance.ChannelCount );
				writer.Write( instance.SamplesPerSecond );
				writer.Write( instance.AudioFrameSize * instance.SamplesPerSecond );
				writer.Write( (ushort)instance.AudioFrameSize );
				writer.Write( (ushort)instance.Depth );

				// set DataBlock
				writer.Write( "data".ToCharArray() );
				writer.Write( instance.Buffer.Length );

				// set audio track
				writer.Write( instance.Buffer );

				return ms.ToArray();
			}
		}
	}
}
