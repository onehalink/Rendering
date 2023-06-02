/**
* Playing A *.wav File By DSound(Windows OS Component)
*/

#include "Engine.h"



Int32 EntryPoint()
{
	Asset asset;
	while (True)
	{
		Char16 filename[512];
		while( !FFileDialog.Open( filename, sizeof(filename) / sizeof(Char16), L"(*.wav)\0*.wav\0", L"./", L"Open *.wav", NullPointer ) );

		U16String u16Filename	= FU16String.Construct(filename);
		U8String path			= FU16String.ToU8String( &u16Filename );

		asset = FAsset.Construct( &path, AssetType_Wave );

		FU8String.Destruct( &path );
		FU16String.Destruct( &u16Filename );

		if ( asset.isLoaded )
			break;
	}

	Wave* wave = &asset.wave;


	const SizeType ASecond = wave->audioFrameSize * wave->samplesPerSecond;

	const SizeType SoundBufferSize		= ASecond / 4;
	const SizeType HalfSoundBufferSize	= SoundBufferSize / 2;


	DirectSound directSound = FDirectSound.Construct( NullPointer, SoundBufferSize, wave->formatTag, wave->channelCount, wave->depth, wave->samplesPerSecond );

	SizeType offset = 0;
	while (True)
	{
		SizeType size = FDirectSound.CalculateWritableBufferSize( &directSound );
		if ( size > HalfSoundBufferSize )
		{
			SizeType readableBufferSize = wave->byteCount - offset;
			if ( size > readableBufferSize )
				size = readableBufferSize;

			FDirectSound.Fill( &directSound, CAST( Byte*, wave->buffer ) + offset, size );

			offset += size;
			if ( offset == wave->byteCount )
				offset = 0;
		}
	}


	FDirectSound.Destruct( &directSound );
	FAsset.Destruct( &asset );

	return 0;
}


int main(int count, char** arguments)
{
	return EntryPoint();
}