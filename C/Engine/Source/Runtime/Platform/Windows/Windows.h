#pragma once

/**
* Windows OS Special APIs
* 
* 
* @remark
* Dont include this header file directly
*/



#if !defined(PLATFORM_WINDOWS)
#error "This is not a Windows app"
#endif


#define WIN32_LEAN_AND_MAIN	// Exclude some stuff that rarely used from <Windows.h>
#define NOMINMAX			// Undefine min and max micros from <minwindef.h>

#include <Windows.h>


#include <dsound.h>
#pragma comment(lib, "dsound")