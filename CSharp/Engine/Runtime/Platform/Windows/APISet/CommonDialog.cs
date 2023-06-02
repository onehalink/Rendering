using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
namespace Engine.Windows.APISet
{
	internal class CommonDialog
	{
		static CommonDialog()
		{
			var dll = DynamicLoader.Load("Comdlg32.dll");

			GetOpenFileNameW = DynamicLoader.GetDelegateForFunctionPointerFromDLL<Open>(dll, "GetOpenFileNameW");
			GetSaveFileNameW = DynamicLoader.GetDelegateForFunctionPointerFromDLL<Open>(dll, "GetSaveFileNameW");
		}


		#region Constants
		public const uint OFN_NOCHANGEDIR	= 0x00000008;
		public const uint OFN_PATHMUSTEXIST	= 0x00000800;
		public const uint OFN_FILEMUSTEXIST = 0x00001000;
		#endregion


		#region Delegates
		public delegate UINT_PTR LPOFNHOOKPROC(HWND _0, UINT _1, WPARAM _2, LPARAM _3);

		public delegate BOOL Open(ref OPENFILENAMEW ofn);
		#endregion


		#region Structs
		[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Size = 152)]
		public struct OPENFILENAMEW
		{
			public DWORD			lStructSize;
			public HWND				hwndOwner;
			public HINSTANCE		hInstance;
			public LPCWSTR			lpstrFilter;
			public LPWSTR			lpstrCustomFilter;
			public DWORD			nMaxCustFilter;
			public DWORD			nFilterIndex;
			public LPWSTR			lpstrFile;
			public DWORD			nMaxFile;
			public LPWSTR			lpstrFileTitle;
			public DWORD			nMaxFileTitle;
			public LPCWSTR			lpstrInitialDir;
			public LPCWSTR			lpstrTitle;
			public DWORD			Flags;
			public WORD				nFileOffset;
			public WORD				nFileExtension;
			public LPCWSTR			lpstrDefExt;
			public LPARAM			lCustData;
			//[MarshalAs(UnmanagedType.FunctionPtr)]
			public LPOFNHOOKPROC	lpfnHook;
			public LPCWSTR			lpTemplateName;

			public IntPtr	pvReserved;
			public DWORD	dwReserved;
			public DWORD	FlagsEx;
		}
		#endregion


		#region Exported Functions
		public static Open GetOpenFileNameW;
		public static Open GetSaveFileNameW;
		#endregion
	}
}
#endif