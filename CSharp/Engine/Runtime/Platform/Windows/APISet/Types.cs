


#if PLATFORM_WINDOWS
global using BYTE		= System.Byte;

global using WORD		= System.UInt16;
global using DWORD		= System.UInt32;

global using ATOM		= System.UInt16;

global using UINT		= System.UInt32;
global using LONG		= System.Int32;
global using ULONG		= System.UInt32;

global using PCWSTR		= System.String;
global using LPCWSTR	= System.String;
global using LPWSTR		= System.String;

global using BOOL		= System.Int32;

global using UINT_PTR	= System.UInt64;
global using LONG_PTR	= System.Int64;

global using LPVOID		= System.IntPtr;

/* Types use for passing & returning polymorphic values */
global using WPARAM		= System.UInt64;
global using LPARAM		= System.Int64;
global using LRESULT	= System.Int64;

global using HRESULT	= System.Int64;


global using HWND		= System.IntPtr;
global using HINSTANCE	= System.IntPtr;
global using HMODULE	= System.IntPtr;
global using HANDLE		= System.IntPtr;

global using HMENU		= System.IntPtr;
global using HICON		= System.IntPtr;
global using HCURSOR	= System.IntPtr;
global using HBRUSH		= System.IntPtr;

global using HDC		= System.IntPtr;
global using HBITMAP	= System.IntPtr;
global using HGDIOBJ	= System.IntPtr;


global using LARGE_INTEGRE = System.Int64;
#endif