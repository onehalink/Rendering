#include "HeapMemory.h"



static HeapMemory Construct(SizeType byteCount)
{
	HeapMemory ret;
	ret.buffer		= FAllocator.Allocate(byteCount);
	ret.byteCount	= byteCount;

	return ret;
}

static Void Destruct(HeapMemory* instance)
{
	if ( !instance )
		return;

	FAllocator.Release( instance->buffer );
}


struct FHeapMemory FHeapMemory = 
{
	Construct,
	Destruct,
};
