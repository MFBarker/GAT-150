#pragma once
#include <cstdint>

namespace neu
{
	//typedef unsigned char u8_t;
	//using u8_t = unsigned char;

	struct Color 
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

	};

	inline std::istream& operator >> (std::istream& stream, Color& color)
	{
		std::string line;
		std::getline(stream, line);

		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;


		return stream;
	}
}
