using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
namespace Engine.Windows.APISet
{
	internal class LibraryLoaderAPI
	{
		static LibraryLoaderAPI()
		{
			var dll = DynamicLoader.Load("kernel32.dll");

			GetModuleHandleW = DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPGetModuleHandleW>(dll, "GetModuleHandleW");
		}


		#region Constants
		#endregion


		#region Delegates
		public delegate HMODULE FPGetModuleHandleW([MarshalAs(UnmanagedType.LPWStr)] string lpModuleName);
		#endregion


		#region Structs
		#endregion


		#region Exported Funtions
		public static FPGetModuleHandleW GetModuleHandleW;
		#endregion
	}
}
#endif