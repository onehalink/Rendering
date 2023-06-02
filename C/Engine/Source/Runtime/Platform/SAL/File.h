#pragma once

#include "../../Core.h"



typedef enum
{
	FileOpen_Read,
	FileOpen_Write,
}
FileOpen;


typedef enum
{
	FileSeek_Begin,
	FileSeek_Current,
	FileSeek_End,
}
FileSeek;


typedef struct
{
	Void* handle;
}
File;


struct FFile
{
	File(*Construct)(const U8String* path, FileOpen open);
	Void(*Destruct)(File* instance);


	Void(*Seek)(File* instance, FileSeek seek, Int64 offset);

	Void(*Read)(File* instance, Void* buffer, SizeType byteCount);
	Void(*Write)(File* instance, const Void* buffer, SizeType byteCount);

	
	Void(*Copy)(const U8String* from, const U8String* to);
	Void(*Delete)(const U8String* path);
	Bool(*Exist)(const U8String* path);
	SizeType(*GetSize)(const U8String* path);
	Void(*Move)(const U8String* from, const U8String* to);

	HeapMemory(*ReadAllBytes)(const U8String* path);
	Void(*WriteAllBytes)(const U8String* path, const Void* buffer, SizeType byteCount);
};

extern ENGINE_API struct FFile FFile;