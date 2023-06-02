using System;
using System.Runtime.InteropServices;



namespace Engine
{
	public class DynamicLoader
	{
		public static IntPtr Load(string path)
		{
#if PLATFORM_WINDOWS
			return LoadLibraryA(path);
#else
#error "No implementation"
#endif
		}

		public static bool Unload(IntPtr dll)
		{
#if PLATFORM_WINDOWS
			return FreeLibrary(dll) != 0;
#else
#error "No implementation"
#endif
		}

		public static T GetDelegateForFunctionPointerFromDLL<T>(IntPtr dll, string exportedFunction) where T : System.Delegate
		{
#if PLATFORM_WINDOWS
			return Marshal.GetDelegateForFunctionPointer<T>( GetProcAddress(dll, exportedFunction) );
#else
#error "No implementation"
#endif
		}


		#region Platform Invoke
#if PLATFORM_WINDOWS
		private const string dll = "kernel32.dll";


		[DllImport(dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
		private extern static IntPtr LoadLibraryA(string path);

		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		private extern static int FreeLibrary(IntPtr dll);

		[DllImport(dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
		private extern static IntPtr GetProcAddress(IntPtr dll, string exportedFunction);
#endif
		#endregion
	}
}
