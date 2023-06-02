#include "Allocator.h"

#include <stdlib.h>



static Void* Allocate(SizeType byteCount)
{
	return malloc(byteCount);
}

static Void Release(Void* pointer)
{
	free(pointer);
}


struct FAllocator FAllocator =
{
	Allocate,
	Release,
};
