using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
using static Engine.Windows.APISet.WinDefinition;


namespace Engine.Windows.APISet
{
	internal class WinUser
	{
		static WinUser()
		{
			var dll = DynamicLoader.Load("user32.dll");

			DefWindowProcW		= DynamicLoader.GetDelegateForFunctionPointerFromDLL<WNDPROC>(dll, "DefWindowProcW");
			RegisterClassExW	= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPRegisterClassExW>(dll, "RegisterClassExW");
			UnregisterClassW	= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPUnregisterClassW>(dll, "UnregisterClassW");
			AdjustWindowRectEx	= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPAdjustWindowRectEx>(dll, "AdjustWindowRectEx");
			CreateWindowExW		= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPCreateWindowExW>(dll, "CreateWindowExW");
			ShowWindow			= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPShowWindow>(dll, "ShowWindow");
			PeekMessageW		= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPPeekMessageW>(dll, "PeekMessageW");
			DispatchMessageW	= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPDispatchMessageW>(dll, "DispatchMessageW");
			GetClientRect		= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPGetClientRect>(dll, "GetClientRect");
			GetDC				= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPGetDC>(dll, "GetDC");
			ReleaseDC			= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPReleaseDC>(dll, "ReleaseDC");
			GetDesktopWindow	= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPGetDesktopWindow>(dll, "GetDesktopWindow");
		}


		#region Constants
		// Window style
		public const int WS_OVERLAPPEDWINDOW = (0x00000000 | 0x00C00000 | 0x00080000 | 0x00040000 | 0x00020000 | 0x00010000);

		// Window messages
		public const uint WM_CREATE			= 0x0001;
		public const uint WM_SIZE			= 0x0005;
		public const uint WM_CLOSE			= 0x0010;
		public const uint WM_DESTROY		= 0x0002;
		public const uint WM_SETFOCUS		= 0x0007;
		public const uint WM_KILLFOCUS		= 0x0008;
		public const uint WM_KEYDOWN		= 0x0100;
		public const uint WM_KEYUP			= 0x0101;
		public const uint WM_LBUTTONDOWN	= 0x0201;
		public const uint WM_RBUTTONDOWN	= 0x0204;
		public const uint WM_MBUTTONDOWN	= 0x0207;
		public const uint WM_MBUTTONUP		= 0x0208;
		public const uint WM_RBUTTONUP		= 0x0205;
		public const uint WM_LBUTTONUP		= 0x0202;
		public const uint WM_MOUSEMOVE		= 0x0200;
		public const uint WM_MOUSEWHEEL		= 0x020A;

		// ShowWindow() commands
		public const int SW_SHOWDEFAULT = 10;

		// PeekMessage() options
		public const int PM_REMOVE = 0x0001;

		// Other
		public const int CW_USEDEFAULT	= unchecked( (int)0x80000000 );
		public const int WHEEL_DELTA	= 120; // Value for rolling one detent
		#endregion


		#region Delegates
		public delegate LRESULT WNDPROC(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		public delegate ATOM FPRegisterClassExW(ref WNDCLASSEXW windowClass);
		public delegate BOOL FPUnregisterClassW([MarshalAs(UnmanagedType.LPWStr)] LPCWSTR lpClassName, HINSTANCE hInstance);

		public delegate BOOL FPAdjustWindowRectEx(ref RECT rect, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle);

		public delegate HWND FPCreateWindowExW(
			DWORD dwExStyle,
			[MarshalAs(UnmanagedType.LPWStr)]
			LPCWSTR lpClassName,
			[MarshalAs(UnmanagedType.LPWStr)]
			LPCWSTR lpWindowName,
			DWORD dwStyle,
			int X,
			int Y,
			int nWidth,
			int nHeight,
			HWND hWndParent,
			HMENU hMenu,
			HINSTANCE hInstance,
			LPVOID lpParam
			);

		public delegate BOOL FPShowWindow(HWND hWnd, int nCmdShow);

		public delegate BOOL FPPeekMessageW(ref MSG msg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
		public delegate LRESULT FPDispatchMessageW(ref MSG msg);

		public delegate BOOL FPGetClientRect(HWND hWnd, ref RECT rect);

		public delegate HDC FPGetDC(HWND hWnd);
		public delegate int FPReleaseDC(HWND hWnd, HDC hDC);

		public delegate HWND FPGetDesktopWindow();
		#endregion


		#region Structs
		[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Size = 80)]
		public struct WNDCLASSEXW
		{
			public UINT			cbSize;
			/* Win 3.x */
			public UINT			style;
			public WNDPROC		lpfnWndProc;
			public int			cbClsExtra;
			public int			cbWndExtra;
			public HINSTANCE	hInstance;
			public HICON		hIcon;
			public HCURSOR		hCursor;
			public HBRUSH		hbrBackground;
			public LPCWSTR		lpszMenuName;
			public LPCWSTR		lpszClassName;
			/* Win 4.0 */
			public HICON		hIconSm;
		}


		// Message structure
		public struct MSG
		{
			public HWND		hwnd;
			public UINT		message;
			public WPARAM	wParam;
			public LPARAM	lParam;
			public DWORD	time;
			public POINT	pt;
		}


		[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Size = 80)]
		public struct CREATESTRUCTW
		{
			public LPVOID		lpCreateParams;
			public HINSTANCE	hInstance;
			public HMENU		hMenu;
			public HWND			hwndParent;
			public int			cy;
			public int			cx;
			public int			y;
			public int			x;
			public LONG			style;
			public LPCWSTR		lpszName;
			public LPCWSTR		lpszClass;
			public DWORD		dwExStyle;
		}
		#endregion


		#region Exported Funtions
		public static WNDPROC				DefWindowProcW;
		public static FPRegisterClassExW	RegisterClassExW;
		public static FPUnregisterClassW	UnregisterClassW;
		public static FPAdjustWindowRectEx	AdjustWindowRectEx;
		public static FPCreateWindowExW		CreateWindowExW;
		public static FPShowWindow			ShowWindow;
		public static FPPeekMessageW		PeekMessageW;
		public static FPDispatchMessageW	DispatchMessageW;
		public static FPGetClientRect		GetClientRect;
		public static FPGetDC				GetDC;
		public static FPReleaseDC			ReleaseDC;
		public static FPGetDesktopWindow	GetDesktopWindow;
		#endregion
	}
}
#endif
