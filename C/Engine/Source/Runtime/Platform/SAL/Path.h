#pragma once

#include "../../Core.h"



struct FPath
{
	// Combine two paths to form a new path
	U8String(*Combine)(const U8String* A, const U8String* B);
	// Test if the last element of path is slash or back slash
	Bool(*IsNormalized)(const U8String* path);
};

extern ENGINE_API struct FPath FPath;