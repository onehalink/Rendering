#include "Bitmap.h"



static const SizeType BitmapFileHeaderSize		= sizeof(BitmapFileHeader);
static const SizeType BitmapInfoHeaderSize		= sizeof(BitmapInfoHeader);
static const SizeType BitmapDefaultBitsOffset	= sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);


static Bitmap Construct(SizeType width, SizeType height, BitmapFormat format)
{
	SizeType channelCount = format == BitmapFormat_B8G8R8 ? 3 : 4;

	Bitmap ret;
	ret.buffer			= FAllocator.Allocate( width * height * channelCount );
	ret.width			= width;
	ret.height			= height;
	ret.format			= format;
	ret.channelCount		= channelCount;

	return ret;
}

static Void Destruct(Bitmap* instance)
{
	if ( !instance )
		return;

	FAllocator.Release( instance->buffer );
}

static Void SetPixel(Bitmap* instance, SizeType x, SizeType y, UInt32 pixel)
{
	FMemory.Copy(
		&pixel,
		CAST( Byte*, instance->buffer ) + ( instance->width * y + x ) * instance->channelCount,
		instance->channelCount
	);
}

static UInt32 GetPixel(const Bitmap* instance, SizeType x, SizeType y)
{
	UInt32 ret;
	FMemory.Copy(
		CAST( const Byte*, instance->buffer ) + ( instance->width * y + x ) * instance->channelCount,
		&ret,
		instance->channelCount
	);

	return ret;
}

static Void FlipHorizontal(Bitmap* instance)
{
	SizeType width		= instance->width;
	SizeType height		= instance->height;
	SizeType channelCount	= instance->channelCount;

	SizeType halfWidth	= width / 2;
	Byte* image			= CAST( Byte*, instance->buffer );

	for (SizeType y = 0; y < height; y++)
		for (SizeType x = 0; x < halfWidth; x++)
			for (SizeType index = 0; index < channelCount; index++)
				SWAP(
					Byte,
					image[ ( width * y + x ) * channelCount + index ],
					image[ ( width * y + (width - 1 - x) ) * channelCount + index ]
				);
}

static Void FlipVertical(Bitmap* instance)
{
	SizeType width		= instance->width;
	SizeType height		= instance->height;
	SizeType channelCount	= instance->channelCount;

	SizeType halfHeight	= height / 2;
	Byte* image			= CAST( Byte*, instance->buffer );

	for (SizeType y = 0; y < halfHeight; y++)
		for (SizeType x = 0; x < width; x++)
			for (SizeType index = 0; index < channelCount; index++)
				SWAP(
					Byte,
					image[ ( width * y + x ) * channelCount + index ],
					image[ ( width * (height - 1 - y) + x ) * channelCount + index ]
				);
}

static Bool IsValid(const Void* buffer, SizeType byteCount)
{
	if ( byteCount < BitmapDefaultBitsOffset )
		return False;

	if ( !FMemory.Equal(buffer, "BM", 2) )
		return False;

	if ( byteCount != CAST( const BitmapFileHeader*, buffer )->size )
		return False;

	const BitmapInfoHeader* info = REINTERPRET_CAST( const BitmapInfoHeader*, buffer, BitmapFileHeaderSize );
	if (
		info->bitCount != 24 &&
		info->bitCount != 32
		)
		return False;

	return True;
}

static Bitmap Decode(const Void* buffer, SizeType byteCount)
{
	if ( !FBitmap.IsValid(buffer, byteCount) )
	{
		//ERROR("Failed to parse a *.bmp file!");

		Bitmap ret = { NullPointer, 0, 0, 0 };
		return ret;
	}

	const BitmapInfoHeader* info = REINTERPRET_CAST( const BitmapInfoHeader*, buffer, BitmapFileHeaderSize );

	SizeType channelCount	= info->bitCount / 8;
	BitmapFormat format	= info->bitCount == 24 ? BitmapFormat_B8G8R8 : BitmapFormat_B8G8R8A8;

	SizeType width	= info->width;
	SizeType height	= info->height;

	SizeType imageSize	= width * height * channelCount;
	Void* imageBuffer	= FAllocator.Allocate(imageSize);
	FMemory.Copy(
		CAST( const Byte*, buffer ) + CAST( const BitmapFileHeader*, buffer )->offset,
		imageBuffer,
		imageSize
	);

	Bitmap ret = { imageBuffer, width, height, format, channelCount };
	return ret;
}

static Memory Encode(const Bitmap* instance)
{
	SizeType imageSize = instance->width * instance->height * instance->channelCount;

	SizeType byteCount	= BitmapDefaultBitsOffset + imageSize;
	Void* buffer		= FAllocator.Allocate(byteCount);
	FMemory.Clear(buffer, BitmapDefaultBitsOffset);
	FMemory.Copy(
		instance->buffer,
		CAST(Byte*, buffer) + BitmapDefaultBitsOffset,
		imageSize
	);

	// set BitmapFileHeader
	BitmapFileHeader* fileHeader	= CAST( BitmapFileHeader*, buffer );
	fileHeader->magic[0]			= 'B';
	fileHeader->magic[1]			= 'M';
	fileHeader->size				= byteCount;
	fileHeader->offset				= BitmapDefaultBitsOffset;

	// set BitmapInfoHeader
	BitmapInfoHeader* infoHeader	= REINTERPRET_CAST( BitmapInfoHeader*, buffer, BitmapFileHeaderSize );
	infoHeader->size				= BitmapInfoHeaderSize;
	infoHeader->width				= instance->width;
	infoHeader->height				= instance->height;
	infoHeader->planes				= 1;
	infoHeader->bitCount			= instance->channelCount * 8;
	infoHeader->imageSize			= imageSize;

	Memory ret = { buffer, byteCount };
	return ret;
}


struct FBitmap FBitmap =
{
	Construct,
	Destruct,
	SetPixel,
	GetPixel,
	FlipHorizontal,
	FlipVertical,
	IsValid,
	Decode,
	Encode,
};
