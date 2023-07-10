#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

class Star
{
public:
	Enginuity::vec2 m_pos;
	Enginuity::vec2 m_vel;
	Enginuity::vec2 m_min = { 0, 0 };
	Enginuity::vec2 m_max = {800, 600};
public:
	Star(const Enginuity::vec2& position, const Enginuity::vec2& velocity) : m_pos{ position }, m_vel{ velocity } {};
	Star(const Enginuity::vec2& position, const Enginuity::vec2& velocity, Enginuity::vec2 min, Enginuity::vec2 max) : m_pos{ position }, m_vel{ velocity }, m_min{ min }, m_max{ max } {};

	void Update(int width, int height) 
	{
		//m_pos += m_vel;
		m_pos = m_pos + m_vel;

		if (m_pos.x > width) m_pos.x = 0;
		if (m_pos.x < 0) m_pos.x = (float)width;
		if (m_pos.y > height) m_pos.y = 0;
		if (m_pos.y < 0) m_pos.y = (float)height;
	}

	void Update()
	{
		//m_pos += m_vel;
		m_pos = m_pos + m_vel;

		if (m_pos.x > m_max.x) m_pos.x = m_min.x;
		if (m_pos.x < m_min.x) m_pos.x = (float)m_max.x;
		if (m_pos.y > m_max.y) m_pos.y = m_min.y;
		if (m_pos.y < m_min.y) m_pos.y = (float)m_max.y;
	}

	void Draw(Enginuity::Renderer& renderer) 
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}
};

int main(int argc, char* argv[])
{

	Enginuity::Renderer renderer;
	
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	std::vector<Enginuity::vec2> points{ {0, 50}, {50, 50}, {50, 0}, {0, 50} };
	std::vector<Enginuity::vec2> otherPoints{ {0, -50}, {-50, -50}, {-50, 0}, {0, -50} };
	std::vector<Enginuity::vec2> morePoints{ {50, 0}, {50, -50}, {0, -50}, {50, 0} };
	std::vector<Enginuity::vec2> extraPoints{ {-50, 0}, {-50, 50}, {0, 50}, {-50, 0} };
	Enginuity::Model model(points);
	Enginuity::Model model2(otherPoints);
	Enginuity::Model model3(morePoints);
	Enginuity::Model model4(extraPoints);

	Enginuity::vec2 v{5, 5};
	v.Normalize();

	while (true)
	{
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		//draw
		renderer.SetColor(255, 255, 255, 0);
		model.Draw(renderer, {400, 300}, 4);
		model2.Draw(renderer, {400, 300}, 4);
		model3.Draw(renderer, {400, 300}, 4);
		model4.Draw(renderer, {400, 300}, 4);

		renderer.EndFrame();
	}

	return 0;
}