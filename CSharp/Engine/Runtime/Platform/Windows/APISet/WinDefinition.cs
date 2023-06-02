using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
namespace Engine.Windows.APISet
{
	internal class WinDefinition
	{
		#region Constants
		#endregion


		#region Delegates
		#endregion


		#region Structs
		public struct RECT
		{
			public LONG left;
			public LONG top;
			public LONG right;
			public LONG bottom;
		}


		public struct POINT
		{
			public LONG x;
			public LONG y;
		}
		#endregion


		#region Exported Funtions
		#endregion
	}
}
#endif
