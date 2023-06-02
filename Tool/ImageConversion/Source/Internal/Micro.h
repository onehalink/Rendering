/**
* Predefined Micros
*/

#pragma once



/**
* C Compiler
* 
* 
* Supported:
* 1.Microsoft C compiler
*/
#if defined(_MSC_VER)
#define COMPILER_MSVC
#else
#error "Unknown C compiler"
#endif


/**
* C Standard
* 
* 
* Required:
* C11 or later
*/
#if !defined(__cplusplus) & (__STDC_VERSION__ < 201112L)
//#error "C11 required"
#endif


/**
* Target Platform
* 
* 
* Supported:
* 1.Windows 64-bit
*/
#if defined(COMPILER_MSVC) & defined(_WIN64)
#define PLATFORM_WINDOWS
#endif


/**
* Export/Import Dynamic Link Library
* 
* 
* Note:
* Used by this project:	[Export]
* Used by the other:	[Import]
*/
#if defined(COMPILER_MSVC)
#define DLL_EXPORT	__declspec(dllexport)
#define DLL_IMPORT	__declspec(dllimport)
#endif

#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API	DLL_EXPORT
#else
#define ENGINE_API	DLL_IMPORT
#endif


/**
* Helper Micros
*/
#define ADD_BRACKET(param)			( ## param ## )
#define COMBINE(paramA, paramB)		paramA ## paramB

#define __STRINGIFY(param)			#param
#define STRINGIFY(param)			__STRINGIFY(param)

#define U8TEXT(text)				COMBINE(u8, text) // Used to represent utf8 encoding string literal
#define U16TEXT(text)				COMBINE( L, text) // Used to represent utf16 encoding string literal


/**
* Math Related
*/
#define __ABSOLUTE(value)					( value < 0 ? -value : value )
#define __CLAMP(value, minimum, maximum)	( value < minimum ? minimum : value > maximum ? maximum : value )
#define __LERP(from, to, amount)			( from + (to - from) * amount )
#define __MAXIMUM(a, b)						( a > b ? a : b )
#define __MINIMUM(a, b)						( a < b ? a : b )

// Return the absolute value of value
#define ABSOLUTE(value)						__ABSOLUTE( ADD_BRACKET(value) )
// Clamp the given value between a range defined by the given minimum and maximum
#define CLAMP(value, minimum, maximum)		__CLAMP( ADD_BRACKET(value), ADD_BRACKET(minimum), ADD_BRACKET(maximum) )
// Clamp the given value between 0 and 1
#define CLAMP01(value)						CLAMP(value, 0, 1)
// Linearly interpolate between "from" and "to" by amount
#define LERP(from, to, amount)				__LERP( ADD_BRACKET(from), ADD_BRACKET(to), ADD_BRACKET(amount) )
// Return the larger of a and b
#define MAXIMUM(a, b)						__MAXIMUM( ADD_BRACKET(a), ADD_BRACKET(b) )
// Return the smaller of a and b
#define MINIMUM(a, b)						__MINIMUM( ADD_BRACKET(a), ADD_BRACKET(b) )
// Swap the value of a and b
#define SWAP(Type, a, b)					{ Type value = a; a = b; b = value; }


/**
* Type Conversion
*/
// Cast argument to the other datatype
#define CAST(Type, argument)						( (Type)(argument) )
// Apply offset to a pointer and reinterpret it to the other pointer datatype
#define REINTERPRET_CAST(Type, pointer, offset)		CAST(Type, CAST(char*, pointer) + offset)