#pragma once
#include <cmath>
#include <utility>

namespace Enginuity 
{
	constexpr float Pi = 3.1415927F;
	constexpr float TwoPi = 6.283195F;
	constexpr float HalfPi = 1.570796F;

	constexpr float RadiansToDegrees(float radians) { return radians * 180.0f / Pi; }
	constexpr float DegreesToRadians(float degrees) { return degrees * Pi / 180.0f; }

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + ((value < 0) ? max : 0);
	}

	inline float Wrap(float value, float max)
	{
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T Max(T a, T b)
	{
		return a > b ? a : b;
	}
	
	template <typename T>
	inline T Min(T a, T b)
	{
		return a < b ? a : b;
	}
	
	template <typename T>
	inline T Clamp(T value, T min, T max)
	{
		if (min > max) std::swap(min, max);

		return (value < min) ? min : (value > max) ? max : value;
	}

	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t) //0 < t < 1
	{
		return (a * (1.0f - t)) + (b * t);
	}
}