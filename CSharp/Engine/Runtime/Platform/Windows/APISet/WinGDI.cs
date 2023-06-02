using System;
using System.Reflection.Metadata;
using System.Runtime.InteropServices;
using System.Security.Cryptography;



#if PLATFORM_WINDOWS
namespace Engine.Windows.APISet
{
	internal class WinGDI
	{
		static WinGDI()
		{
			var dll = DynamicLoader.Load("gdi32.dll");

			CreateCompatibleDC	= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPCreateCompatibleDC>(dll, "CreateCompatibleDC");
			DeleteDC			= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPDeleteDC>(dll, "DeleteDC");
			CreateDIBSection	= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPCreateDIBSection>(dll, "CreateDIBSection");
			SelectObject		= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPSelectObject>(dll, "SelectObject");
			DeleteObject		= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPDeleteObject>(dll, "DeleteObject");
			BitBlt				= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPBitBlt>(dll, "BitBlt");
		}


		#region Constants
		/* DIB color table identifiers */
		public const int DIB_RGB_COLORS = 0; /* color table in RGBs */
		public const int DIB_PAL_COLORS = 1; /* color table in palette indices */

		/* Ternary raster operations */
		public const DWORD SRCCOPY = (DWORD)0x00CC0020; /* dest = source                   */
		#endregion


		#region Delegates
		public delegate HDC FPCreateCompatibleDC(HDC hdc);
		public delegate BOOL FPDeleteDC(HDC hdc);

		public delegate HBITMAP FPCreateDIBSection(HDC hdc, ref BITMAPINFO bmi, UINT usage, ref IntPtr ppvBits, HANDLE hSection, DWORD offset);

		public delegate HGDIOBJ FPSelectObject(HDC hdc, HGDIOBJ h);
		public delegate BOOL FPDeleteObject(HGDIOBJ ho);

		public delegate BOOL FPBitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);
		#endregion


		#region Structs
		public struct BITMAPINFOHEADER
		{
			public DWORD	biSize;
			public LONG		biWidth;
			public LONG		biHeight;
			public WORD		biPlanes;
			public WORD		biBitCount;
			public DWORD	biCompression;
			public DWORD	biSizeImage;
			public LONG		biXPelsPerMeter;
			public LONG		biYPelsPerMeter;
			public DWORD	biClrUsed;
			public DWORD	biClrImportant;
		}


		public struct RGBQUAD
		{
			public BYTE rgbBlue;
			public BYTE rgbGreen;
			public BYTE rgbRed;
			public BYTE rgbReserved;
		}


		public struct BITMAPINFO
		{
			public BITMAPINFOHEADER	bmiHeader;
			public RGBQUAD			bmiColors;
		}
		#endregion


		#region Exported Funtions
		public static FPCreateCompatibleDC	CreateCompatibleDC;
		public static FPDeleteDC			DeleteDC;
		public static FPCreateDIBSection	CreateDIBSection;
		public static FPSelectObject		SelectObject;
		public static FPDeleteObject		DeleteObject;
		public static FPBitBlt				BitBlt;
		#endregion
	}
}
#endif