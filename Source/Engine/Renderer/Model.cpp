#include "Model.h"
#include <sstream>


namespace Enginuity
{
	bool Model::Load(const std::string& filename)
	{
		std::string buffer;
		Enginuity::readFile(filename, buffer);

		std::istringstream stream(buffer);

		stream >> m_color;

		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);

		for (size_t i = 0; i < numPoints; i++)
		{
			vec2 point;

			stream >> point;

			m_points.push_back(point);
		}

		return true;
	}
	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
	{
		if (m_points.empty()) 
		{
			return;
		}

		for(size_t index = 0; index < m_points.size() - 1; index++)
		{
			vec2 p1 = (m_points[index] * scale).Rotate(rotation) + position;
			vec2 p2 = (m_points[index + 1] * scale).Rotate(rotation) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
		
	}
	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	float Model::GetRadius()
	{
		if (m_radius != 0) return m_radius;

		for (auto& point : m_points)
		{
			float length = point.Length();
			m_radius = Max(m_radius, length);
		}

		return m_radius;
	}
}


