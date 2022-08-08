#include "Color.h"

namespace neu
{
	const Color white{ 255,255,255,255 };
	const Color black{ 0,0,0,255 };
	const Color red{ 255,0,0,255 };
	const Color green{ 0,255,0,255 };
	const Color blue{ 0,0,255,255 };



	std::istream& operator >> (std::istream& stream, Color& color)
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