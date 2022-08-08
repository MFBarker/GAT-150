#pragma once

namespace math
{
	constexpr float Pi = (3.14159265359f);//180 deg
	constexpr float TwoPi = (2 * 3.14159265359f);//360 deg
	constexpr float HalfPi = (3.14159265359f / 2);//90 deg

	constexpr float DegToRad(float degrees)
	{
		return degrees * (Pi / 180);
	}

	constexpr float RadToDeg(float radians)
	{
		return radians * (180 / Pi);
	}

	int sqr(int v);
	inline int half(int v) { return v / 2; };
}
