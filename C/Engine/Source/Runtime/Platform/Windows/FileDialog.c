#include "FileDialog.h"

#include "Windows.h"



typedef BOOL(APIENTRY*DialogCallback)(OPENFILENAMEW*);

static Bool OpenDialog(Char16* inBuffer, SizeType inSize, const Char16* filters, const Char16* initDirectory, const Char16* title, Void* owner, DialogCallback Fn)
{
	FMemory.Clear( inBuffer, sizeof(Char16) * inSize );

	OPENFILENAMEW openFilename;
	FMemory.Clear( &openFilename, sizeof(OPENFILENAMEW) );
	openFilename.lStructSize		= sizeof(OPENFILENAMEW);
	openFilename.hwndOwner			= CAST(HWND, owner);
	openFilename.lpstrFilter		= filters;
	openFilename.lpstrFile			= inBuffer;
	openFilename.nMaxFile			= inSize;
	openFilename.lpstrInitialDir	= initDirectory;
	openFilename.lpstrTitle			= title;
	openFilename.Flags				= OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	return Fn( &openFilename );
}


static Bool Open(Char16* inBuffer, SizeType inSize, const Char16* filters, const Char16* initDirectory, const Char16* title, Void* owner)
{
	return OpenDialog(inBuffer, inSize, filters, initDirectory, title, owner, GetOpenFileNameW);
}

static Bool Save(Char16* inBuffer, SizeType inSize, const Char16* filters, const Char16* initDirectory, const Char16* title, Void* owner)
{
	return OpenDialog(inBuffer, inSize, filters, initDirectory, title, owner, GetSaveFileNameW);
}


struct FFileDialog FFileDialog = 
{
	Open,
	Save,
};
