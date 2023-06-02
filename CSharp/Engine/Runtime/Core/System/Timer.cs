


#if PLATFORM_WINDOWS
using static Engine.Windows.APISet.ProfileAPI;
#endif


namespace Engine
{
	public class Timer
	{
		/// <summary>
		/// Time point
		/// </summary>
		/// <remarks> Unit is second </remarks>
		private float start;


		public Timer() => Reset();


		/// <summary>
		/// Record current system time
		/// </summary>
		public void Reset() => start = CurrentSystemTime();

		/// <summary>
		/// Time elapsed in seconds
		/// </summary>
		public float Elapsed() => CurrentSystemTime() - start;


		private static double period = -1;
		private static float CurrentSystemTime()
		{
#if PLATFORM_WINDOWS
			if( period < 0 )
			{
				LARGE_INTEGRE frequency = default;
				QueryPerformanceFrequency(ref frequency);

				period = 1.0 / frequency;
			}

			LARGE_INTEGRE counter = default;
			QueryPerformanceCounter(ref counter);

			return ( (float)( period * counter ) );
#else
#error "No implementation"
#endif
		}
	}
}
