#pragma once

#include "File.h"
#include "Path.h"



typedef enum
{
	DirectoryEntryEnumOption_File		= 1 << 0,
	DirectoryEntryEnumOption_Directory	= 1 << 1,

	DirectoryEntryEnumOption_All		= DirectoryEntryEnumOption_File | DirectoryEntryEnumOption_Directory,
}
DirectoryEntryEnumOption;


struct FDirectory
{
	Void(*Copy)(const U8String* from, const U8String* to);
	Void(*Create)(const U8String* path);
	Void(*Delete)(const U8String* path, Bool isRecursive);
	Bool(*Exist)(const U8String* path);
	Void(*Move)(const U8String* from, const U8String* to);

	/**
	* @remark
	* The return that the container's datatype is U8String
	*/
	DynamicArray(*EnumEntries)(const U8String* path, DirectoryEntryEnumOption enumOption);
};

extern ENGINE_API struct FDirectory FDirectory;