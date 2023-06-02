using System;
using System.Runtime.InteropServices;



#if PLATFORM_WINDOWS
using static Engine.Windows.APISet.DSound;
using static Engine.Windows.APISet.WinUser;


namespace Engine.Windows
{
	public class DirectSound
	{
		// Used to place in cached pcm(pulse code modulation)
		private byte[] buffer;

		private IDirectSound		sound;
		private IDirectSoundBuffer	soundBuffer;
		private int					writePosition;

		private IntPtr pSound;
		private IntPtr pSoundBuffer;


		public DirectSound(HWND nativeWindowsWindowHandle, int preallocatedBufferSize, WaveFormatTag waveFormatTag, int channelCount, int depth, int samplesPerSecond)
		{
			if( nativeWindowsWindowHandle == IntPtr.Zero )
				nativeWindowsWindowHandle = GetDesktopWindow();

			{
				DirectSoundCreate(IntPtr.Zero, out pSound, IntPtr.Zero);

				sound = Marshal.GetObjectForIUnknown(pSound) as IDirectSound;

				var errorCode = sound.SetCooperativeLevel(nativeWindowsWindowHandle, DSSCL_NORMAL);
			}

			unsafe
			{
				int AudioFrameSize = depth / 8 * channelCount;

				var format				= new WAVEFORMATEX();
				format.wFormatTag		= (ushort)waveFormatTag;
				format.nChannels		= (ushort)channelCount;
				format.nSamplesPerSec	= (uint)samplesPerSecond;
				format.nAvgBytesPerSec	= (uint)(AudioFrameSize * samplesPerSecond);
				format.nBlockAlign		= (ushort)AudioFrameSize;
				format.wBitsPerSample	= (ushort)depth;
				format.cbSize			= 0;

				var descriptor				= new DSBUFFERDESC();
				descriptor.dwSize			= (uint)Marshal.SizeOf<DSBUFFERDESC>();
				descriptor.dwFlags			= DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLVOLUME;
				descriptor.dwBufferBytes	= (uint)preallocatedBufferSize;
				descriptor.lpwfxFormat		= &format;

				/*
				IntPtr output;
				sound.CreateSoundBuffer(in descriptor, out output, IntPtr.Zero);

				var iid = new Guid(0x279AFA85, 0x4981, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60);

				Marshal.QueryInterface(output, ref iid, out pSoundBuffer);
				Marshal.Release(output);
				*/

				sound.CreateSoundBuffer(in descriptor, out pSoundBuffer, IntPtr.Zero);
				soundBuffer = Marshal.GetObjectForIUnknown(pSoundBuffer) as IDirectSoundBuffer;
			}

			this.buffer			= new byte[preallocatedBufferSize];
			this.writePosition	= 0;

			Play();
		}
		
		~DirectSound()
		{
			Marshal.Release(pSound);
			Marshal.Release(pSoundBuffer);
			Marshal.FinalReleaseComObject(sound);
			Marshal.FinalReleaseComObject(soundBuffer);
		}


		public unsafe void Fill(byte[] buffer, int offset, int length)
		{
			fixed( byte* pBuffer = &buffer[offset] )
			{
				IntPtr dataPointer = new IntPtr(pBuffer);

				int fixedSize = this.buffer.Length;
				if ( length > fixedSize )
					return;

				uint writableBufferSize;
				{
					writableBufferSize = (uint)( fixedSize - writePosition );
					if ( writableBufferSize > length )
						writableBufferSize = (uint)length;

					IntPtr	lockedBuffer;
					DWORD	lockedSize;
					soundBuffer.Lock( (uint)writePosition, writableBufferSize, out lockedBuffer, out lockedSize, IntPtr.Zero, IntPtr.Zero, 0 );
					Memory.Copy( (void*)dataPointer, (void*)lockedBuffer, (int)lockedSize );
					soundBuffer.Unlock( lockedBuffer, lockedSize, IntPtr.Zero, 0 );

					writePosition += (int)writableBufferSize;
					if ( writePosition == fixedSize )
						writePosition = 0;

					length -= (int)writableBufferSize;
				}

				if ( length != 0 )
				{
					dataPointer			= IntPtr.Add( dataPointer, (int)writableBufferSize );
					writableBufferSize	= (uint)length;

					IntPtr lockedBuffer;
					DWORD lockedSize;
					soundBuffer.Lock( (uint)writePosition, writableBufferSize, out lockedBuffer, out lockedSize, IntPtr.Zero, IntPtr.Zero, 0 );
					Memory.Copy( (void*)dataPointer, (void*)lockedBuffer, (int)lockedSize );
					soundBuffer.Unlock( lockedBuffer, lockedSize, IntPtr.Zero, 0 );

					writePosition += (int)writableBufferSize;
				}
			}
		}

		public void Play()
		{
			soundBuffer.Play(0, 0, DSBPLAY_LOOPING);
		}

		public void Stop()
		{
			soundBuffer.Stop();
		}

		public void SetVolumn(float volumn)
		{
			// todo..
		}

		public int CalculateWritableBufferSize()
		{
			DWORD readCursor;
			DWORD writeCursor;
			soundBuffer.GetCurrentPosition(out readCursor, out writeCursor);

			if ( writePosition > readCursor )
				return buffer.Length - ( writePosition - (int)readCursor );
			else
				return (int)readCursor - writePosition;
		}
	}
}
#endif