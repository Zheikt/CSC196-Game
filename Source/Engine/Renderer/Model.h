#pragma once
#include "Core/Core.h"
#include "Core/Color.h"
#include "Renderer.h"
#include <vector>

namespace Enginuity 
{
	class Model 
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {};

		bool Load(const std::string& filename);
		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		float GetRadius();

	private:
		std::vector<vec2> m_points;
		float m_radius = 0;
		Color m_color;
	};
}