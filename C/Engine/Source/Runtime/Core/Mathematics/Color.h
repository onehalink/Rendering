#pragma once

#include "Math.h"



typedef union
{
	struct
	{
		RealType r;
		RealType g;
		RealType b;
		RealType a;
	};
	RealType components[4];
}
Color;


struct FColor
{
	const Color Black;
	const Color White;
	const Color Red;
	const Color Green;
	const Color Blue;
	const Color Yellow;
	const Color Cyan;
	const Color Magneta;


	RealType(*Luminance)(const Color* instance);
	
	Color(*Darkened)(const Color* instance, RealType amount);
	Color(*Lightened)(const Color* instance, RealType amount);

	/**
	* Convert to linear color space
	*
	*
	* @remark
	* Gamma0.45 to Gamma1.0
	*/
	Color(*ToLinear)(const Color* instance);
	/**
	* Convert to gamma color space
	*
	*
	* @remark
	* Gamma1.0 to Gamma0.45
	*/
	Color(*ToSrgb)(const Color* instance);


	Color(*Add)(const Color* leftHandSide, const Color* rightHandSide);
	Color(*Subtract)(const Color* leftHandSide, const Color* rightHandSide);
	Color(*Multiply)(const Color* leftHandSide, const Color* rightHandSide);
	Color(*MultiplyCS)(const Color* instance, RealType scalar);
	Color(*Divide)(const Color* instance, RealType scalar);
};

extern ENGINE_API struct FColor FColor;