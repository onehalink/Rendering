#include "Directory.h"

#if defined(PLATFORM_WINDOWS)
#include "../Windows/Windows.h"
#endif



static Void Copy(const U8String* from, const U8String* to)
{
	if ( !FDirectory.Exist(to) )
		FDirectory.Create(to);

	DynamicArray entries = FDirectory.EnumEntries(from, DirectoryEntryEnumOption_All);
	for ( SizeType index = 0; index < entries.count; index++ )
	{
		U8String* entry = CAST( U8String*, FDynamicArray.IndexAt( &entries, index ) );

		U8String combinedFrom	= FPath.Combine( from, entry );
		U8String combinedTo		= FPath.Combine( to, entry );

		if ( FFile.Exist( &combinedFrom ) )
			FFile.Copy( &combinedFrom, &combinedTo );

		if ( FDirectory.Exist( &combinedFrom ) )
			FDirectory.Copy( &combinedFrom, &combinedTo );

		FU8String.Destruct( &combinedTo );
		FU8String.Destruct( &combinedFrom );

		FU8String.Destruct(entry);
	}

	FDynamicArray.Destruct( &entries );
}

static Void Create(const U8String* path)
{
#if defined(PLATFORM_WINDOWS)
	U16String u16 = FU8String.ToU16String(path);
	CreateDirectoryW( u16.buffer, NullPointer );

	FU16String.Destruct( &u16 );
#else
#error "No implementation"
#endif
}

static Void Delete(const U8String* path, Bool isRecursive)
{
	DynamicArray entries = FDirectory.EnumEntries(path, DirectoryEntryEnumOption_All);
	if ( !isRecursive )
	{
		if ( entries.count != 0 )
		{
			FDynamicArray.Destruct( &entries );

			return;
		}
	}
	else
		for ( SizeType index = 0; index < entries.count; index++ )
		{
			U8String* entry = CAST( U8String*, FDynamicArray.IndexAt( &entries, index ) );
			
			U8String combined = FPath.Combine( path, entry );

			if ( FFile.Exist( &combined ))
				FFile.Delete( &combined );

			if ( FDirectory.Exist( &combined ) )
				FDirectory.Delete( &combined, isRecursive );

			FU8String.Destruct( &combined );

			FU8String.Destruct(entry);
		}

	FDynamicArray.Destruct( &entries );

#if defined(PLATFORM_WINDOWS)
	U16String u16 = FU8String.ToU16String(path);
	RemoveDirectoryW( u16.buffer );

	FU16String.Destruct( &u16 );
#else
#error "No implementation"
#endif
}

static Bool Exist(const U8String* path)
{
#if defined(PLATFORM_WINDOWS)
	File file = FFile.Construct(path, FileOpen_Read);

	if ( GetLastError() == ERROR_FILE_NOT_FOUND )
		return False;

	FFile.Destruct( &file );

	U16String u16		= FU8String.ToU16String(path);
	Bool isDirectory	= GetFileAttributesW( u16.buffer ) & FILE_ATTRIBUTE_DIRECTORY;

	FU16String.Destruct( &u16 );

	if (isDirectory)
		return True;
#else
#error "No implementation"
#endif

	return False;
}

static Void Move(const U8String* from, const U8String* to)
{
#if defined(PLATFORM_WINDOWS)
	FFile.Move(from, to);
#else
#error "No implementation"
#endif
}

static DynamicArray EnumEntries(const U8String* path, DirectoryEntryEnumOption enumOption)
{
	DynamicArray ret = FDynamicArray.Construct( 0, sizeof(U8String) );

#if defined(PLATFORM_WINDOWS)
	U8String suffix		= FU8String.Construct("*.*");
	U8String filter		= FPath.Combine( path, &suffix );
	U16String u16Filter	= FU8String.ToU16String( &filter );

	FU8String.Destruct( &filter );
	FU8String.Destruct( &suffix );

	WIN32_FIND_DATAW findData;
	HANDLE findHandle = FindFirstFileW( u16Filter.buffer, &findData );

	FU16String.Destruct( &u16Filter );

	if ( findHandle == INVALID_HANDLE_VALUE )
		return ret;

	do
	{
		// ignore default entries("." and "..")
		if ( findData.cFileName[0] == '.' )
			continue;

		Bool selectFile			= enumOption & DirectoryEntryEnumOption_File;
		Bool selectDirectory	= enumOption & DirectoryEntryEnumOption_Directory;

		Bool isFile			= findData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE;
		Bool isDirectory	= findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;

		if (
			( selectFile		&& isFile		) ||
			( selectDirectory	&& isDirectory	)
			)
		{
			/*
			U16String u16Entry	= FU16String.Construct( findData.cFileName );
			U8String entry		= FU16String.ToU8String( &u16Entry );

			FU16String.Destruct( &u16Entry );

			FDynamicArray.Add( &ret, &entry );
			*/

			U16String u16Entry = { findData.cFileName, FUnicode.GetUTF16ElementCount( findData.cFileName, 0x0000 ) };
			U8String entry		= FU16String.ToU8String( &u16Entry );

			FDynamicArray.Add( &ret, &entry );
		};
	}
	while ( FindNextFileW( findHandle, &findData ) );

	FindClose(findHandle);
#else
#error "No implementation"
#endif

	return ret;
}


struct FDirectory FDirectory = 
{
	Copy,
	Create,
	Delete,
	Exist,
	Move,
	EnumEntries,
};
