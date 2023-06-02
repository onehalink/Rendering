using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
using static Engine.Windows.APISet.LibraryLoaderAPI;
using static Engine.Windows.APISet.WinDefinition;
using static Engine.Windows.APISet.WinUser;


namespace Engine.Windows
{
	public class Window
	{
		public HWND Handle { get; private set; }
		public int Width { get; set; }
		public int Height { get; set; }
		public string className;


		public Window(string title = "Default Window", int width = 1280, int height = 720, IntPtr userParam = default, string className = "Class Entry")
		{
			var instance = GetModuleHandleW("");

			// style
			DWORD style			= WS_OVERLAPPEDWINDOW;
			DWORD extendStyle	= 0;

			// register window class
			{
				var windowClass				= new WNDCLASSEXW();
				windowClass.cbSize			= (uint)Marshal.SizeOf<WNDCLASSEXW>();
				windowClass.lpfnWndProc		= WindowProcedure;
				windowClass.hInstance		= instance;
				windowClass.lpszClassName	= className;

				RegisterClassExW(ref windowClass);
			}

			// resized to expected size
			int realWidth;
			int realHeight;
			{
				RECT rect	= new RECT();
				rect.left	= 0;
				rect.top	= 0;
				rect.right	= width;
				rect.bottom	= height;

				AdjustWindowRectEx(ref rect, style, 0, extendStyle);

				realWidth	= rect.right - rect.left;
				realHeight	= rect.bottom - rect.top;
			}

			// create and display
			HWND handle = CreateWindowExW(
				extendStyle,
				className,
				title,
				style,
				CW_USEDEFAULT, CW_USEDEFAULT, realWidth, realHeight,
				IntPtr.Zero, IntPtr.Zero, instance, userParam
				);
			ShowWindow(handle, SW_SHOWDEFAULT);

			Handle			= handle;
			Width			= realWidth;
			Height			= realHeight;
			this.className	= className;
		}
	
		~Window() => UnregisterClassW( className, GetModuleHandleW("") );


		public void Update()
		{
			MSG message = new MSG();

			while( PeekMessageW(ref message, Handle, 0, 0, PM_REMOVE) > 0 )
				DispatchMessageW(ref message);
		}


		private static IntPtr userParam = default;
		// cache the index of the last mouse button
		private static WPARAM lastWParam;
		private unsafe static LRESULT WindowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
		{
			var eventSystem = ( (EventSystem*)userParam );

			switch(message)
			{
				case WM_CREATE:
					userParam = Marshal.ReadIntPtr( new IntPtr(lParam) );
					break;
				case WM_SIZE:
					{
						int width	= ( (int)lParam >>  0 ) & 0xFFFF;
						int height	= ( (int)lParam >> 16 ) & 0xFFFF;

						eventSystem->AddWindowResizeEvent(width, height);
					}
					break;
				case WM_CLOSE:
				case WM_DESTROY:
					eventSystem->AddWindowCloseEvent(true);
					break;

				case WM_KEYDOWN:
				case WM_KEYUP:
					eventSystem->AddKeyEvent(
						(Key)wParam,
						message == WM_KEYDOWN ? ButtonState.Pressed : ButtonState.Released
						);
					break;

				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
				case WM_MBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_RBUTTONUP:
				case WM_MBUTTONUP:
					{
						// The last mouse button had been released if isZero
						bool isZero = wParam == 0;

						eventSystem->AddMouseButtonEvent(
							isZero ? (MouseButton)lastWParam : (MouseButton)wParam,
							isZero ? ButtonState.Released : ButtonState.Pressed
							);

						lastWParam = wParam;
					}
					break;
				case WM_MOUSEMOVE:
					{
						RECT rect = new RECT();
						GetClientRect(handle, ref rect);

						int height = rect.bottom - rect.top;

						int x = ( (int)wParam >>  0 ) & 0xFFFF;
						int y = ( (int)wParam >> 16 ) & 0xFFFF;

						eventSystem->AddMouseMoveEvent( x, height - 1 - y );
					}
					break;
				case WM_MOUSEWHEEL:
					eventSystem->AddMouseScrollWheelScrollEvent( ( (int)wParam >> 16 ) & 0xFFFF );
					break;

				default:
					return DefWindowProcW(handle, message, wParam, lParam);
			}

			return 1;
		}
	}
}
#endif