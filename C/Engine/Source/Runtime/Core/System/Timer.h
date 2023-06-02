#pragma once

#include "../Base.h"



typedef struct
{
	/**
	* Time point
	* 
	* 
	* @remark
	* Unit is second
	*/
	RealType start;
}
Timer;


struct FTimer
{
	Timer(*Construct)();


	// Record current system time and store the result to instance->start
	Void(*Reset)(Timer* instance);

	// Measured in seconds
	RealType(*Elapsed)(const Timer* instance);
};

extern ENGINE_API struct FTimer FTimer;
