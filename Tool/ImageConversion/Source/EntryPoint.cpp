#include "Image.h"

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>



static std::vector<std::filesystem::path> GetFiles(const std::filesystem::path& path, const std::vector<std::string>& filters)
{
	std::vector<std::filesystem::path> ret;
	for (auto& entry : std::filesystem::recursive_directory_iterator(path))
	{
		if ( !entry.is_regular_file() )
			continue;

		for (auto& filter : filters)
			if ( filter == entry.path().extension() )
			{
				ret.push_back(entry);
				break;
			}
	}

	return ret;
}

static void ForceTo24Bits(const std::filesystem::path& path)
{
	for (const auto& selected : GetFiles( path, {".bmp"} ))
	{
		auto filesize	= std::filesystem::file_size(selected);
		auto buffer		= new char[filesize];

		std::cout << "[Convert To 24-Bit]Processing " << selected << "\n";

		{
			std::fstream in(selected, std::ios::in | std::ios::binary);
			in.read(buffer, filesize);
		}

		Bitmap from	= FBitmap.Decode(buffer, filesize);
		if ( from.channelCount == 3 )
		{
			FBitmap.Destruct(&from);
			continue;
		}


		Bitmap to = FBitmap.Construct(from.width, from.height, BitmapFormat_B8G8R8);
		for (SizeType y = 0; y < from.height; y++)
			for (SizeType x = 0; x < from.width; x++)
				FBitmap.SetPixel(
					&to,
					x, y,
					FBitmap.GetPixel(&from, x, y)
				);

		Memory encoded = FBitmap.Encode(&to);
		{
			std::fstream out(selected, std::ios::out | std::ios::binary | std::ios::trunc);
			out.write( reinterpret_cast<char*>(encoded.buffer), encoded.byteCount );
		}

		FMemory.Destruct(&encoded);
		FBitmap.Destruct(&to);
		FBitmap.Destruct(&from);
	}
}


int EntryPoint()
{
	constexpr Bool IsForceTo24Bits = true;


	auto inFolder = std::filesystem::path("C:\\Dev\\Rendering\\Asset\\cg");
	auto outFolder = std::filesystem::path("./OutputFolder/");

	if ( std::filesystem::is_directory(outFolder) )
		std::filesystem::remove_all(outFolder);

	std::filesystem::create_directory(outFolder);

	for (auto& selected : GetFiles(inFolder, { ".png", ".jpg"}))
	{
		auto filesize	= std::filesystem::file_size(selected);
		auto buffer		= new char[filesize];

		std::cout << "Processing " << selected << "\n";

		std::fstream in(selected, std::ios::in | std::ios::binary);
		in.read(buffer, filesize);

		Memory converted = { nullptr, 0 };
		{
			if ( selected.extension() == ".png" )
				converted = Convert<ImageFormat::PNG, ImageFormat::BMP>(buffer, filesize);

			if ( selected.extension() == ".jpg" )
				converted = Convert<ImageFormat::JPG, ImageFormat::BMP>(buffer, filesize);
		}

		std::fstream out( outFolder / selected.replace_extension(".bmp").filename(), std::ios::out | std::ios::binary );
		out.write( reinterpret_cast<char*>(converted.buffer), converted.byteCount );

		FMemory.Destruct(&converted);
		delete[] buffer;
	}

	if (IsForceTo24Bits)
		ForceTo24Bits(outFolder);

	return 0;
}


int main()
{
	return EntryPoint();
}