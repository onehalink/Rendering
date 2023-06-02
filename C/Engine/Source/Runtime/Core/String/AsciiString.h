#pragma once

#include "U8String.h"

#include "../Container/DynamicArray.h"



typedef U8String AsciiString;


struct FAsciiString
{
	AsciiString(*Construct)(const Char8* inAsciiString);
	Void(*Destruct)(AsciiString* instance);


	/**
	* @remark
	* return -1 if not found
	*/
	Int32(*IndexOf)(const AsciiString* instance, Char8 character);
	Int32(*LastIndexOf)(const AsciiString* instance, Char8 character);

	AsciiString(*Substring)(const AsciiString* instance, SizeType startIndex, SizeType length);
	/**
	* @remark
	* The return that the container's datatype is AsciiString
	*/
	DynamicArray(*Split)(const AsciiString* instance, Char8 separator);

	AsciiString(*ToLower)(const AsciiString* instance);
	AsciiString(*ToUpper)(const AsciiString* instance);


	AsciiString(*Add)(const AsciiString* leftHandSide, const AsciiString* rightHandSide);
	AsciiString(*AddSC)(const AsciiString* instance, Char8 character);
	AsciiString(*AddCS)(Char8 character, const AsciiString* instance);

	Bool(*Equal)(const AsciiString* leftHandSide, const AsciiString* rightHandSide);
};

extern ENGINE_API struct FAsciiString FAsciiString;