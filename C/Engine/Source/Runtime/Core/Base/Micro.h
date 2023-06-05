#pragma once

/**
* Predefined Micros
*/



/**
* Compiler
* 
* 
* @remark
* Supported:
* 1.Microsoft C compiler
*/
#if defined(_MSC_VER)
#define COMPILER_MSVC
#else
#error "Unknown C compiler"
#endif


/**
* Standard
* 
* 
* @remark
* Required:
* C11 or later
*/
#if !defined(__cplusplus) & (__STDC_VERSION__ < 201112)
#error "C11 required"
#endif


/**
* Platform
* 
* 
* @remark
* Supported:
* 1.Windows 64-bit
*/
#if defined(COMPILER_MSVC) & defined(_WIN64)
#define PLATFORM_WINDOWS
#else
#error "Current platform is not supported"
#endif


/**
* Export/Import dynamic link library
* 
* 
* @remark
* Used by this:			[Export]
* Used by the other:	[Import]
*/
#if defined(COMPILER_MSVC)
#define DLL_EXPORT	__declspec(dllexport)
#define DLL_IMPORT	__declspec(dllimport)
#else
#error "DLL_EXPORT and DLL_IMPORT are undefined"
#endif

#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API DLL_EXPORT
#else
#define ENGINE_API DLL_IMPORT
#endif


// Check runtime error
#define ASSERT(condition, ...)	\
do								\
{								\
	if( !condition )			\
	{							\
								\
	}							\
}								\
while(0)


/** Type conversion */
#define CAST(Type, param)						( (Type)(param) )							// Cast param to the other datatype
#define REINTERPRET_CAST(Type, pointer, offset)	CAST( Type, CAST(char*, pointer) + offset )	// Apply offset in bytes to a pointer and reinterpret it to the other pointer datatype


/** Math related */
#define SWAP(Type, a, b)	do { Type temporary = a; a = b; b = temporary; } while(0) // Swap the value of a and b