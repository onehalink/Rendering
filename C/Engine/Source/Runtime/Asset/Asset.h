#pragma once

#include "Bitmap.h"
#include "Wave.h"

#include "../Platform/SAL/File.h"
#include "../Platform/SAL/Path.h"



typedef enum
{
	AssetType_Bitmap,
	AssetType_Wave,
}
AssetType;


typedef struct
{
	AssetType	type;
	Bool		isLoaded;


	union
	{
		Bitmap	bitmap;
		Wave	wave;
	};
}
Asset;


struct FAsset
{
	U8String AssetFolder;


	Asset(*Construct)(const U8String* path, AssetType type);
	Void(*Destruct)(Asset* instance);
};

extern ENGINE_API struct FAsset FAsset;