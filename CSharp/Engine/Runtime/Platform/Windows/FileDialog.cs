using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
using static Engine.Windows.APISet.CommonDialog;


namespace Engine.Windows
{
	public class FileDialog
	{
		public static bool Open(out string outputSelectedFile, string filter = "(*.*)\0*.*\0", string initDirectory = "./", string title = "Open file..", HWND owner = default)
		{
			return OpenDialog(out outputSelectedFile, filter, initDirectory, title, owner, GetOpenFileNameW);
		}

		public static bool Save(out string outputSelectedFile, string filter = "(*.*)\0*.*\0", string initDirectory = "./", string title = "Save as..", HWND owner = default)
		{
			return OpenDialog(out outputSelectedFile, filter, initDirectory, title, owner, GetSaveFileNameW);
		}


		private static bool OpenDialog(out string outputSelectedFile, string filter, string initDirectory, string title, HWND owner, Open Fn)
		{
			var ofn				= new OPENFILENAMEW();
			ofn.lStructSize		= (uint)Marshal.SizeOf<OPENFILENAMEW>();
			ofn.hwndOwner		= owner;
			ofn.lpstrFilter		= filter;
			ofn.lpstrFile		= new string( new char[256] );
			ofn.nMaxFile		= (uint)ofn.lpstrFile.Length;
			ofn.lpstrInitialDir	= initDirectory;
			ofn.lpstrTitle		= title;
			ofn.Flags			= OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			var errorCode = Fn(ref ofn);
			outputSelectedFile = ofn.lpstrFile;

			return errorCode != 0;
		}
	}
}
#endif
