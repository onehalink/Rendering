#pragma once

/**
* Base Types Redefined
*/



typedef char				SByte;
typedef unsigned char		UByte;
typedef UByte				Byte;

typedef SByte				Int8;
typedef short				Int16;
typedef int					Int32;
typedef long long			Int64;

typedef Byte				UInt8;
typedef unsigned short		UInt16;
typedef unsigned int		UInt32;
typedef unsigned long long	UInt64;

typedef float				Float32;
typedef double				Float64;

typedef SByte				Char8;
typedef UInt16				Char16;
typedef UInt32				Char32;
typedef Char32				CodePoint; // Used to represent unicode(0 - 0x10FFFF)

typedef Byte				Bool;

typedef void				Void;


typedef UInt64				SizeType;
typedef Float32				RealType;