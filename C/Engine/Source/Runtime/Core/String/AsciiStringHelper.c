#include "AsciiStringHelper.h"



static const Char8* SkipWhiteSpace(const Char8* cStyleString)
{
	const Char8* p = cStyleString;

	while (
		*p == '\r' ||
		*p == '\n' ||
		*p == '\t' ||
		*p == ' '
		)
		p++;

	return p;
}

static Bool IsNumber(Char8 value)
{
	return value >= '0' && value <= '9';
}

static Int32 FindDot(const Char8* cStyleString)
{
	const Char8* p = cStyleString;

	SizeType index = 0;
	while ( *p != 0x00 )
	{
		if ( *p == '.' )
			return index;

		p++;
		index++;
	}

	return -1;
}


static Bool TryParseBool(Bool* outputResult, const Char8* inAsciiString)
{
	const Char8* pointer = SkipWhiteSpace(inAsciiString);

	Bool parse;
	switch ( *pointer )
	{
	case 'f':
	case 'F':
		parse = False;
		break;
	case 't':
	case 'T':
		parse = True;
		break;
	default:
		return False;
	}

	if (outputResult)
		*outputResult = parse;

	return True;
}

static Bool TryParseInt32(Int32* outputResult, const Char8* inAsciiString)
{
	const Char8* pointer = SkipWhiteSpace(inAsciiString);

	Int32 sign = 1;
	switch ( *pointer )
	{
	case '-':
		sign = -1;
	case '+':
		pointer++;
		break;
	}

	if ( !IsNumber( *pointer ) )
		return False;

	Int32 number = 0;
	while ( IsNumber( *pointer ) )
	{
		number *= 10;
		number += *pointer - '0';

		pointer++;
	}

	if (outputResult)
		*outputResult = number * sign;

	return True;
}

static Bool TryParseFloat32(Float32* outputResult, const Char8* inAsciiString)
{
	Int32 integerPart;
	if ( !FAsciiStringHelper.TryParseInt32( &integerPart, inAsciiString ) )
		return False;

	Float32 fractionPart;
	{
		Int32 numerator		= 0;
		Int32 denominator	= 1;

		Int32 dotIndex = FindDot(inAsciiString);
		if ( dotIndex != -1 )
		{
			const Char8* pointer = inAsciiString + ( dotIndex + 1 );

			while ( IsNumber( *pointer ) )
			{
				numerator *= 10;
				numerator += *pointer - '0';

				denominator *= 10;

				pointer++;
			}
		}

		fractionPart = CAST(Float32, numerator) / denominator;
	}

	if (outputResult)
	{
		Int32 sign = integerPart < 0 ? -1 : 1;
		
		*outputResult = integerPart + fractionPart * sign;
	}

	return True;
}

static Bool TryConvertBool(Char8* inBuffer, SizeType inSize, Bool value)
{
	if ( !value )
	{
		const SizeType MinimumSize	= 5 + 1;
		const Char8* Text			= "False";

		if ( inSize < MinimumSize )
			return False;

		for ( SizeType index = 0; index < MinimumSize; index++ )
			inBuffer[index] = Text[index];
	}
	else
	{
		const SizeType MinimumSize	= 4 + 1;
		const Char8* Text			= "True";

		if ( inSize < MinimumSize )
			return False;

		for ( SizeType index = 0; index < MinimumSize; index++ )
			inBuffer[index] = Text[index];
	}

	return True;
}

static Bool TryConvertInt32(Char8* inBuffer, SizeType inSize, Int32 value)
{
	SizeType digits = 1;
	{
		Int32 temporary = value < 0 ? -value : value;
		while ( temporary >= 10 )
		{
			digits++;

			temporary /= 10;
		}
	}

	if ( inSize < digits + 1 )
		return False;

	for ( SizeType index = 0; index < digits; index++ )
	{
		Int32 divisor = 1;
		for ( Int32 iteration = digits - 1 - index; iteration > 0; iteration-- )
			divisor *= 10;

		Int32 number	= value / divisor;
		value			-= number * divisor;

		inBuffer[index] = '0' + number;
	}

	// insert terminated character
	inBuffer[digits] = 0x00;

	return True;
}

static Bool TryConvertFloat32(Char8* inBuffer, SizeType inSize, Float32 value)
{
	const Float32 Scale			= 100000;
	const SizeType ZeroCount	= 5;

	if ( FAsciiStringHelper.TryConvertInt32( inBuffer, inSize - 1, value * Scale ) )
	{
		SizeType length = FUnicode.GetUTF8ElementCount(inBuffer, 0x00);

		SizeType dotIndex = length - ZeroCount;
		for ( Int32 index = length + 1; index > dotIndex; index-- )
			inBuffer[index] = inBuffer[ index - 1 ];

		inBuffer[dotIndex] = '.';
	}
	else
		return False;

	return True;
}


struct FAsciiStringHelper FAsciiStringHelper = 
{
	TryParseBool,
	TryParseInt32,
	TryParseFloat32,
	TryConvertBool,
	TryConvertInt32,
	TryConvertFloat32,
};
