#pragma once

#include "Type.h"



struct FAllocator
{
	Void*(*Allocate)(SizeType byteCount);
	Void(*Release)(Void* pointer);
};

extern struct FAllocator FAllocator;