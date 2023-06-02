#include "U32String.h"

#include "U8String.h"
#include "U16String.h"



static U32String Construct(const Char32* utf32)
{
	SizeType count = 0;
	while ( utf32[count] != 0x00000000 )
		count++;

	Char32* buffer = CAST( Char32*, FAllocator.Allocate( sizeof(Char32) * ( count + 1 ) ) );

	FMemory.Copy( utf32, buffer, sizeof(Char32) * ( count + 1 ) );

	U32String ret = { buffer, count };
	return ret;
}

static Void Destruct(U32String* instance)
{
	if ( !instance )
		return;

	FAllocator.Release( instance->buffer );
}

static U8String ToU8String(const U32String* instance)
{
	SizeType count	= FUnicode.GetUTF8ElementCountFromCodePoints( instance->buffer, instance->count );
	Char8* buffer	= CAST( Char8*, FAllocator.Allocate( sizeof(Char8) * ( count + 1 ) ) );

	// insert terminated character
	buffer[count] = 0x00;

	SizeType offset = 0;
	for ( SizeType index = 0; index < instance->count; index++ )
		offset += FUnicode.ToUTF8( buffer + offset, instance->buffer[index] );

	U8String ret = { buffer, count };
	return ret;
}

static U16String ToU16String(const U32String* instance)
{
	SizeType count = FUnicode.GetUTF16ElementCountFromCodePoints( instance->buffer, instance->count );
	Char16* buffer = CAST( Char16*, FAllocator.Allocate( sizeof(Char16) * ( count + 1 ) ) );

	// insert terminated character
	buffer[count] = 0x0000;

	SizeType offset = 0;
	for ( SizeType index = 0; index < instance->count; index++ )
		offset += FUnicode.ToUTF16( buffer + offset, instance->buffer[index] );

	U16String ret = { buffer, count };
	return ret;
}


struct FU32String FU32String = 
{
	Construct,
	Destruct,
	ToU8String,
	ToU16String,
};
