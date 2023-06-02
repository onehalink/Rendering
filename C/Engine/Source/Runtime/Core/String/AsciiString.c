#include "AsciiString.h"



static AsciiString Construct(const Char8* inAsciiString)
{
	return FU8String.Construct(inAsciiString);
}

static Void Destruct(AsciiString* instance)
{
	FU8String.Destruct(instance);
}

static Int32 IndexOf(const AsciiString* instance, Char8 character)
{
	for ( SizeType index = 0; index < instance->count; index++ )
		if ( instance->buffer[index] == character )
			return index;

	return -1;
}

static Int32 LastIndexOf(const AsciiString* instance, Char8 character)
{
	for( Int32 index = instance->count - 1; index >= 0; index-- )
		if ( instance->buffer[index] == character )
			return index;

	return -1;
}

static AsciiString Substring(const AsciiString* instance, SizeType startIndex, SizeType length)
{
	SizeType count	= length;
	Char8* buffer	= CAST( Char8*, FAllocator.Allocate( sizeof(Char8) * ( count + 1 ) ) );

	// insert terminated character
	buffer[count] = 0x00;

	FMemory.Copy( instance->buffer + startIndex, buffer, sizeof(Char8) * count );

	AsciiString ret = { buffer, count };
	return ret;
}

static DynamicArray Split(const AsciiString* instance, Char8 separator)
{
	DynamicArray ret = FDynamicArray.Construct( 0, sizeof(AsciiString) );

	SizeType startIndex = 0;
	for ( SizeType index = 0; index < instance->count; index++ )
		if ( instance->buffer[index] == separator )
		{
			AsciiString substring = FAsciiString.Substring( instance, startIndex, index - startIndex );
			FDynamicArray.Add( &ret, &substring );

			startIndex = index + 1;
		}

	AsciiString substring = FAsciiString.Substring( instance, startIndex, instance->count - startIndex );
	FDynamicArray.Add( &ret, &substring );

	return ret;
}

static AsciiString ToLower(const AsciiString* instance)
{
	SizeType count	= instance->count;
	Char8* buffer	= CAST( Char8*, FAllocator.Allocate( sizeof(Char8) * ( count + 1 ) ) );

	// insert terminated character
	buffer[count] = 0x00;

	for ( SizeType index = 0; index < count; index++ )
	{
		Char8 value		= instance->buffer[index];
		Int32 offset	= 0;

		if ( value >= 'A' && value <= 'Z' )
			offset = 32;

		buffer[index] = value + offset;
	}

	AsciiString ret = { buffer, count };
	return ret;
}

static AsciiString ToUpper(const AsciiString* instance)
{
	SizeType count	= instance->count;
	Char8* buffer	= CAST( Char8*, FAllocator.Allocate( sizeof(Char8) * ( count + 1 ) ) );

	// insert terminated character
	buffer[count] = 0x00;

	for ( SizeType index = 0; index < count; index++ )
	{
		Char8 value		= instance->buffer[index];
		Int32 offset	= 0;

		if ( value >= 'a' && value <= 'z' )
			offset = -32;

		buffer[index] = value + offset;
	}

	AsciiString ret = { buffer, count };
	return ret;
}

static AsciiString Add(const AsciiString* leftHandSide, const AsciiString* rightHandSide)
{
	SizeType count	= leftHandSide->count + rightHandSide->count;
	Char8* buffer	= CAST( Char8*, FAllocator.Allocate( sizeof(Char8) * ( count + 1 ) ) );

	// insert terminated character
	buffer[count] = 0x00;

	FMemory.Copy( leftHandSide->buffer, buffer, sizeof(Char8) * leftHandSide->count );
	FMemory.Copy( rightHandSide->buffer, buffer + leftHandSide->count, sizeof(Char8) * rightHandSide->count );

	AsciiString ret = { buffer, count };
	return ret;
}

static AsciiString AddSC(const AsciiString* instance, Char8 character)
{
	AsciiString rhs = { &character, 1 };

	return FAsciiString.Add( instance, &rhs );
}

static AsciiString AddCS(Char8 character, const AsciiString* instance)
{
	AsciiString lhs = { &character, 1 };

	return FAsciiString.Add( &lhs, instance );
}

static Bool Equal(const AsciiString* leftHandSide, const AsciiString* rightHandSide)
{
	if ( leftHandSide->count != rightHandSide->count )
		return False;

	if (
		!FMemory.Equal(
			leftHandSide->buffer,
			rightHandSide->buffer,
			sizeof(Char8) * leftHandSide->count
		)
		)
		return False;

	return True;
}


struct FAsciiString FAsciiString = 
{
	Construct,
	Destruct,
	IndexOf,
	LastIndexOf,
	Substring,
	Split,
	ToLower,
	ToUpper,
	Add,
	AddSC,
	AddCS,
	Equal,
};
