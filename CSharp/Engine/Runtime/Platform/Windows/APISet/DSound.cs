using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
namespace Engine.Windows.APISet
{
	internal class DSound
	{
		static DSound()
		{
			var dll = DynamicLoader.Load("dsound.dll");

			DirectSoundCreate = DynamicLoader.GetDelegateForFunctionPointerFromDLL<FPDirectSoundCreate>(dll, "DirectSoundCreate");
		}


		#region Constants
		// The function completed successfully
		public const HRESULT DS_OK = 0;

		// Flags
		public const int DSSCL_NORMAL		= 0x00000001;
		public const int DSSCL_PRIORITY		= 0x00000002;
		public const int DSSCL_EXCLUSIVE	= 0x00000003;
		public const int DSSCL_WRITEPRIMARY	= 0x00000004;

		public const uint DSBPLAY_LOOPING = 0x00000001;

		public const uint DSBCAPS_GLOBALFOCUS			= 0x00008000;
		public const uint DSBCAPS_CTRLPOSITIONNOTIFY	= 0x00000100;
		public const uint DSBCAPS_GETCURRENTPOSITION2	= 0x00010000;
		public const uint DSBCAPS_CTRLVOLUME			= 0x00000080;
		#endregion


		#region Delegates
		public delegate HRESULT FPDirectSoundCreate(IntPtr pcGuidDevice, out IntPtr ppDS, IntPtr pUnkOuter);
		#endregion


		#region Interfaces
		[ComImport]
		[Guid("279AFA83-4981-11CE-A521-0020AF0BE560")]
		[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
		public interface IDirectSound
		{
			HRESULT CreateSoundBuffer(in DSBUFFERDESC pcDSBufferDesc, out IntPtr ppDSBuffer, IntPtr pUnkOuter);
			HRESULT GetCaps(IntPtr pDSCaps);
			HRESULT DuplicateSoundBuffer(IntPtr pDSBufferOriginal, out IntPtr ppDSBufferDuplicate);
			HRESULT SetCooperativeLevel(HWND hwnd, DWORD dwLevel);
			HRESULT Compact();
			HRESULT GetSpeakerConfig(out DWORD pdwSpeakerConfig);
			HRESULT SetSpeakerConfig(DWORD dwSpeakerConfig);
			HRESULT Initialize(IntPtr pcGuidDevice);
		}


		[ComImport]
		[Guid("279AFA85-4981-11CE-A521-0020AF0BE560")]
		[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
		public interface IDirectSoundBuffer
		{
			HRESULT GetCaps(IntPtr pDSBufferCaps);
			HRESULT GetCurrentPosition(out DWORD pdwCurrentPlayCursor, out DWORD pdwCurrentWriteCursor);
			HRESULT GetFormat(out WAVEFORMATEX pwfxFormat, DWORD dwSizeAllocated, out DWORD pdwSizeWritten);
			HRESULT GetVolume(out LONG plVolume);
			HRESULT GetPan(out ULONG plPan);
			HRESULT GetFrequency(out DWORD pdwFrequency);
			HRESULT GetStatu(out DWORD pdwStatus);
			HRESULT Initialize(IntPtr pDirectSound, ref DSBUFFERDESC pcDSBufferDesc);
			HRESULT Lock(DWORD dwOffset, DWORD dwBytes, out LPVOID ppvAudioPtr1, out DWORD pdwAudioBytes1, IntPtr ppvAudioPtr2Unused, IntPtr pdwAudioBytes2Unused, DWORD dwFlags);
			HRESULT Play(DWORD dwReserved1, DWORD dwPriority, DWORD dwFlags);
			HRESULT SetCurrentPosition(DWORD dwNewPosition);
			HRESULT SetFormat(ref WAVEFORMATEX pcfxFormat);
			HRESULT SetVolume(LONG lVolume);
			HRESULT SetPan(LONG lPan);
			HRESULT SetFrequency(DWORD dwFrequency);
			HRESULT Stop();
			HRESULT Unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2);
			HRESULT Restore();
		}
		#endregion


		#region Structs
		public struct GUID
		{
			public uint		Data1;
			public ushort	Data2;
			public ushort	Data3;
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
			public byte[]	Data4;
		}


		public struct WAVEFORMATEX
		{
			public WORD		wFormatTag;         /* format type */
			public WORD		nChannels;          /* number of channels (i.e. mono, stereo...) */
			public DWORD	nSamplesPerSec;     /* sample rate */
			public DWORD	nAvgBytesPerSec;    /* for buffer estimation */
			public WORD		nBlockAlign;        /* block size of data */
			public WORD		wBitsPerSample;     /* number of bits per sample of mono data */
			public WORD		cbSize;             /* the count in bytes of the size of */
			/* extra information (after cbSize) */
		}


		public unsafe struct DSBUFFERDESC
		{
			public DWORD			dwSize;
			public DWORD			dwFlags;
			public DWORD			dwBufferBytes;
			public DWORD			dwReserved;
			public WAVEFORMATEX*	lpwfxFormat;
			public GUID				guid3DAlgorithm;
		}
		#endregion


		#region Exported Funtions
		public static FPDirectSoundCreate DirectSoundCreate;
		#endregion
	}
}
#endif
