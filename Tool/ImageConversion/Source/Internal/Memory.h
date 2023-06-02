#pragma once

#include "Allocator.h"
#include "Micro.h"
#include "Enum.h"



typedef struct
{
	Void*		buffer;
	SizeType	byteCount;
}
Memory;


struct FMemory
{
	Memory(*Construct)(SizeType byteCount);
	Void(*Destruct)(Memory* instance);


	Void(*Clear)(Void* buffer, SizeType byteCount);
	Void(*Copy)(const Void* from, Void* to, SizeType byteCount);
	Bool(*Equal)(const Void* bufferA, const Void* bufferB, SizeType byteCount);
};

extern struct FMemory FMemory;