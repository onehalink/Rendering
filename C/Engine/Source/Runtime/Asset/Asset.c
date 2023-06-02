#include "Asset.h"



static Asset Construct(const U8String* path, AssetType type)
{
	Asset ret;
	ret.type		= type;
	ret.isLoaded	= False;

	U8String combined = FPath.Combine( &FAsset.AssetFolder, path );

	if ( !FFile.Exist( &combined ) )
	{
		FU8String.Destruct( &combined );

		return ret;
	}

	HeapMemory loaded = FFile.ReadAllBytes( &combined );

	FU8String.Destruct( &combined );

	Void* buffer		= loaded.buffer;
	SizeType byteCount	= loaded.byteCount;
	switch (type)
	{
	case AssetType_Bitmap:
		if ( FBitmap.IsValid(buffer, byteCount) )
		{
			ret.bitmap = FBitmap.Decode(buffer, byteCount);

			ret.isLoaded = True;
		}
		break;
	case AssetType_Wave:
		if ( FWave.IsValid(buffer, byteCount) )
		{
			ret.wave = FWave.Decode(buffer, byteCount);

			ret.isLoaded = True;
		}
		break;
	}

	FHeapMemory.Destruct( &loaded );

	return ret;
}

static Void Destruct(Asset* instance)
{
	if ( !instance || !instance->isLoaded )
		return;

	instance->isLoaded = False;

	switch ( instance->type )
	{
	case AssetType_Bitmap:
		FBitmap.Destruct( &instance->bitmap );
		break;
	case AssetType_Wave:
		FWave.Destruct( &instance->wave );
		break;
	}
}


struct FAsset FAsset = 
{
	{ NullPointer, 0 },

	Construct,
	Destruct,
};
