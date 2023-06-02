/**
* Used To Decode/Encode Uncompressed 24-bit(B8G8R8) or 32-bit(B8G8R8A8) *.bmp File
*/

#pragma once

#include "Memory.h"



#pragma pack(push, 2)
/**
* Reference from https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
* 
* 
* @remark
* The size in bytes of the struct must be 14
*/
typedef struct
{
	Byte	magic[2];
	UInt32	size;
	UInt32	reserved;
	UInt32	offset;
}
BitmapFileHeader;
#pragma pack(pop)


/**
* Reference from https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
* 
* 
* @remark
* The size in bytes of the struct should be 40
*/
typedef struct
{
	UInt32 size;
	UInt32 width;
	UInt32 height;
	UInt16 planes;
	UInt16 bitCount;
	UInt32 compression;
	UInt32 imageSize;
	UInt32 xPixelsPerMeter;
	UInt32 yPixelsPerMeter;
	UInt32 colorUsed;
	UInt32 colorImportant;
}
BitmapInfoHeader;


typedef enum
{
	BitmapFormat_B8G8R8,
	BitmapFormat_B8G8R8A8,
}
BitmapFormat;


/*
typedef union
{
	struct { Byte b, g, r; };
	Byte components[3];
}
BitmapPixel24;


typedef union
{
	struct { Byte b, g, r, a; };
	Byte components[4];
}
BitmapPixel32;
*/


typedef struct
{
	Void* buffer;

	SizeType		width;
	SizeType		height;
	BitmapFormat	format;
	SizeType		channelCount;
}
Bitmap;


struct FBitmap
{
	Bitmap(*Construct)(SizeType width, SizeType height, BitmapFormat format);
	Void(*Destruct)(Bitmap* instance);


	Void(*SetPixel)(Bitmap* instance, SizeType x, SizeType y, UInt32 pixel);
	UInt32(*GetPixel)(const Bitmap* instance, SizeType x, SizeType y);

	Void(*FlipHorizontal)(Bitmap* instance);
	Void(*FlipVertical)(Bitmap* instance);


	Bool(*IsValid)(const Void* buffer, SizeType byteCount);

	Bitmap(*Decode)(const Void* buffer, SizeType byteCount);
	Memory(*Encode)(const Bitmap* instance);
};

extern ENGINE_API struct FBitmap FBitmap;