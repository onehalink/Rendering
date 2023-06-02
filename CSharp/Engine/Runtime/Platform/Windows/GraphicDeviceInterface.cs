using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
using static Engine.Windows.APISet.WinGDI;
using static Engine.Windows.APISet.WinUser;


namespace Engine.Windows
{
	public class GraphicDeviceInterface
	{
		public delegate void RenderCallback(IntPtr RenderTarget);


		private HWND	handle;
		private HDC		targetDC;
		private HDC		memoryDC;


		public GraphicDeviceInterface(HWND nativeWindowsWindowHandle)
		{
			handle		= nativeWindowsWindowHandle;
			targetDC	= GetDC(handle);
			memoryDC	= CreateCompatibleDC(targetDC);
		}

		~GraphicDeviceInterface()
		{
			if (
				( handle != IntPtr.Zero ) &&
				( targetDC != IntPtr.Zero )
				)
				ReleaseDC(handle, targetDC);

			if( memoryDC != IntPtr.Zero )
				DeleteDC(memoryDC);
		}


		public void Present(int width, int height, RenderCallback Fn)
		{
			var bmi						= new BITMAPINFO();
			bmi.bmiHeader.biSize		= (uint)Marshal.SizeOf<BITMAPINFO>();
			bmi.bmiHeader.biWidth		= width;
			bmi.bmiHeader.biHeight		= height;
			bmi.bmiHeader.biBitCount	= 8 * 4;
			bmi.bmiHeader.biPlanes		= 1;

			IntPtr RenderTarget = default;
			HBITMAP hBitmap = CreateDIBSection(memoryDC, ref bmi, DIB_RGB_COLORS, ref RenderTarget, IntPtr.Zero, 0);

			if (
				( Fn != null ) &&
				( RenderTarget != IntPtr.Zero )
				)
				Fn(RenderTarget);

			if( hBitmap != IntPtr.Zero )
			{
				SelectObject(memoryDC, hBitmap);
				BitBlt(targetDC, 0, 0, width, height, memoryDC, 0, 0, SRCCOPY);
				DeleteObject(hBitmap);
			}
		}
	}
}
#endif