#pragma once

namespace math
{
	const float Pi = (3.14159265359f);//180 deg
	const float TwoPi = (2 * 3.14159265359f);//360 deg
	const float HalfPi = (3.14159265359f / 2);//90 deg

	inline float DegToRad(float degrees)
	{
		return degrees * (Pi / 180);
	}

	inline float RadToDeg(float radians)
	{
		return radians * (180 / Pi);
	}

	int sqr(int v);
	inline int half(int v) { return v / 2; };
}
