#include "Timer.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Platform/Windows/Windows.h"
#endif



static RealType CurrentSystemTime()
{
#if defined(PLATFORM_WINDOWS)
	static Float64 period = -1;
	if ( period < 0 )
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		period = 1.0 / frequency.QuadPart;
	}

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	return period * counter.QuadPart;
#else
#error "No implementation"
#endif
}


static Timer Construct()
{
	Timer ret;
	FTimer.Reset( &ret );

	return ret;
}

static Void Reset(Timer* instance)
{
	instance->start = CurrentSystemTime();
}

static RealType Elapsed(const Timer* instance)
{
	return CurrentSystemTime() - instance->start;
}


struct FTimer FTimer = 
{
	Construct,
	Reset,
	Elapsed,
};
