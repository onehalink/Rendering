#pragma once

#include "../../Core.h"



typedef struct
{
	// Used to place in cached pcm(pulse code modulation)
	Void*		buffer;
	SizeType	byteCount;

	Void*		sound;
	Void*		soundBuffer;
	SizeType	writePosition;
}
DirectSound;


struct FDirectSound
{
	DirectSound(*Construct)(Void* nativeWindowsWindowHandle, SizeType preallocatedBufferSize, SizeType waveFormatTag, SizeType channelCount, SizeType depth, SizeType samplesPerSecond);
	Void(*Destruct)(DirectSound* instance);


	Void(*Fill)(DirectSound* instance, const Void* buffer, SizeType byteCount);

	Void(*Play)(DirectSound* instance);
	Void(*Stop)(DirectSound* instance);
	Void(*SetVolumn)(DirectSound* instance, RealType volumn);


	SizeType(*CalculateWritableBufferSize)(const DirectSound* instance);
};

extern ENGINE_API struct FDirectSound FDirectSound;