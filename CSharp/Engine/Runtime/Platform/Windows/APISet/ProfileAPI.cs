using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
namespace Engine.Windows.APISet
{
	internal class ProfileAPI
	{
		static ProfileAPI()
		{
			var dll = DynamicLoader.Load("kernel32.dll");

			QueryPerformanceCounter		= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPQueryPerformanceCounter>(dll, "QueryPerformanceCounter");
			QueryPerformanceFrequency	= DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPQueryPerformanceFrequency>(dll, "QueryPerformanceFrequency");
		}


		#region Constants
		#endregion


		#region Delegates
		public delegate BOOL FPQueryPerformanceCounter(ref LARGE_INTEGRE performanceCount);
		public delegate BOOL FPQueryPerformanceFrequency(ref LARGE_INTEGRE frequency);
		#endregion


		#region Structs
		#endregion


		#region Exported Funtions
		public static FPQueryPerformanceCounter		QueryPerformanceCounter;
		public static FPQueryPerformanceFrequency	QueryPerformanceFrequency;
		#endregion
	}
}
#endif
