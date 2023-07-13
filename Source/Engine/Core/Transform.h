#pragma once
#include "Vector2.h"

namespace Enginuity
{
	class Transform
	{
	public:
		vec2 position;
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const vec2& position, float rotation, float scale = 1.0f)
			: position(position), rotation(rotation), scale(scale)
		{}
	};
}