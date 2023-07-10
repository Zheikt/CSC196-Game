#include "Model.h"

namespace Enginuity
{
	void Model::Draw(Renderer& renderer, const vec2& position, float scale)
	{
		if (m_points.empty()) 
		{
			return;
		}

		for(size_t index = 0; index < m_points.size() - 1; index++)
		{
			vec2 p1 = (m_points[index] * scale) + position;
			vec2 p2 = (m_points[index + 1] * scale) + position;

			

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
		
	}
}


