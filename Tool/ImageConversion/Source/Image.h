#pragma once

extern "C"
{
// decode *.bmp
#include "Internal/Bitmap.h"
}

// decode *.png
#include "ThirdParty/lodepng/lodepng.h"

// decode *.jpg
#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/stb/stb_image.h"


#include <cmath>



enum class ImageFormat
{
	BMP,
	PNG,
	JPG,
};


template<ImageFormat Source, ImageFormat Destination> Memory Convert(const void* buffer, SizeType byteCount);

template<> Memory Convert<ImageFormat::PNG, ImageFormat::BMP>(const void* buffer, SizeType byteCount);
template<> Memory Convert<ImageFormat::JPG, ImageFormat::BMP>(const void* buffer, SizeType byteCount);


#pragma region Details
template<> 
Memory Convert<ImageFormat::PNG, ImageFormat::BMP>(const void* buffer, SizeType byteCount)
{
	unsigned char* image;
	unsigned int width;
	unsigned int height;
	lodepng_decode32(&image, &width, &height, reinterpret_cast<const unsigned char*>(buffer), byteCount);

	auto bitmap = FBitmap.Construct(width, height, BitmapFormat_B8G8R8A8);
	for(int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			struct RGBA { Byte r, g, b, a; };
			struct BGRA { Byte b, g, r, a; };

			auto from	= reinterpret_cast<RGBA*>(image)[width * y + x];
			auto& to	= reinterpret_cast<BGRA*>(bitmap.buffer)[width * y + x];

			to.b = from.b;
			to.g = from.g;
			to.r = from.r;
			to.a = from.a;
		}

	FBitmap.FlipVertical(&bitmap);
	Memory ret = FBitmap.Encode(&bitmap);
	FBitmap.Destruct(&bitmap);

	return ret;
}

template<> 
Memory Convert<ImageFormat::JPG, ImageFormat::BMP>(const void* buffer, SizeType byteCount)
{
	int width;
	int height;
	int components;
	auto image = stbi_loadf_from_memory(reinterpret_cast<const stbi_uc*>(buffer), byteCount, &width, &height, &components, 4);

	auto bitmap = FBitmap.Construct(width, height, BitmapFormat_B8G8R8A8);
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			struct Color { float r, g, b, a; };
			struct BGRA { Byte b, g, r, a; };

			auto from = reinterpret_cast<Color*>(image)[width * y + x];
			auto& to = reinterpret_cast<BGRA*>(bitmap.buffer)[width * y + x];

			// convert to gamma color space from linear
			to.b = std::pow(from.b, 0.45) * 255;
			to.g = std::pow(from.g, 0.45) * 255;
			to.r = std::pow(from.r, 0.45) * 255;
			to.a = std::pow(from.a, 0.45) * 255;
		}

	STBI_FREE(image);

	FBitmap.FlipVertical(&bitmap);
	Memory ret = FBitmap.Encode(&bitmap);
	FBitmap.Destruct(&bitmap);

	return ret;
}
#pragma endregion