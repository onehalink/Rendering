// See https://aka.ms/new-console-template for more information
//Console.WriteLine("Hello, World!");


using Engine;
using Engine.Windows;



var selected = "";
if ( !FileDialog.Open(out selected, "(*.wav)\0*.*\0") )
	return;

var wave = Wave.Decode( File.ReadAllBytes(selected) );


int ASecond				= wave.AudioFrameSize * wave.SamplesPerSecond;
int soundBufferSize		= ASecond / 4;
int halfSoundBufferSize = soundBufferSize / 2;

var directSound = new DirectSound( IntPtr.Zero, soundBufferSize, wave.FormatTag, wave.ChannelCount, wave.Depth, wave.SamplesPerSecond );

int offset = 0;
while(true)
{
	int size = directSound.CalculateWritableBufferSize();

	if( size > halfSoundBufferSize )
	{
		int readableBufferSize = wave.Buffer.Length - offset;
		if ( size > readableBufferSize )
			size = readableBufferSize;

		directSound.Fill( wave.Buffer, offset, size );

		offset += size;
		if ( offset == wave.Buffer.Length )
			offset = 0;
	}
}