#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

class Star
{
public:
	Enginuity::Vector2 m_pos;
	Enginuity::Vector2 m_vel;
public:
	Star(const Enginuity::Vector2& position, const Enginuity::Vector2& velocity) : m_pos{ position }, m_vel{ velocity } {}

	void Update(int width, int height) 
	{
		m_pos += m_vel;
		//m_pos = m_pos + m_vel;

		if (m_pos.x > width) m_pos.x = 0;
		if (m_pos.x < 0) m_pos.x = (float)width;
		if (m_pos.y > height) m_pos.y = 0;
		if (m_pos.y < 0) m_pos.y = (float)height;
	}

	void Draw(Enginuity::Renderer& renderer) 
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}
};

int main(int argc, char* argv[])
{
	/*Enginuity::seedRandom((unsigned int)time(nullptr));

	for(int i = 1; i < 100; i++) cout << Enginuity::randomf(15, 20) << endl;*/

	Enginuity::Renderer renderer;
	vector<Star> stars;
	
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	for (size_t i = 0; i < 1000; i++)
	{
		Enginuity::Vector2 pos(Enginuity::Vector2(Enginuity::random(renderer.GetWidth()), Enginuity::random(renderer.GetHeight())));
		Enginuity::Vector2 vel(Enginuity::Vector2(Enginuity::randomf(1,4), Enginuity::randomf(1, 4)));

		stars.push_back(Star(pos, vel));
	}

	while (true)
	{
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//draw
		Enginuity::Vector2 vel(1.0f, 0.3f);

		for (auto& star : stars)
		{
			star.Update(renderer.GetWidth(), renderer.GetHeight());

			renderer.SetColor(Enginuity::random(256), Enginuity::random(256), Enginuity::random(256), Enginuity::random(256));
			renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		/*
		for (size_t i = 0; i < 500; i++)
		{
			Enginuity::Vector2 pos(Enginuity::randomf(renderer.GetWidth()), Enginuity::randomf(renderer.GetHeight()));
			Enginuity::Vector2 pos2(Enginuity::randomf(renderer.GetWidth()), Enginuity::randomf(renderer.GetHeight()));

			renderer.DrawPoint(pos.x, pos.y);
			//renderer.DrawLine(pos.x, pos.y, pos2.x, pos2.y);
		}*/

		renderer.EndFrame();
	}

	/*Enginuity::g_memoryTracker.DisplayInfo();
	int* p = new int;
	Enginuity::g_memoryTracker.DisplayInfo();
	delete p;
	Enginuity::g_memoryTracker.DisplayInfo();

	Enginuity::Time timer;
	for (long long i = 0; i < LLONG_MAX; i++) {}
	cout << timer.GetElapsedSeconds() << endl;*/

	/*auto start = std::chrono::high_resolution_clock::now();

	for (long i = 0; i < LONG_MAX; i++) {}

	auto end = std::chrono::high_resolution_clock::now();

	cout << (std::chrono::duration_cast<std::chrono::nanoseconds>)(end - start).count() << endl;*/

	/*cout << Enginuity::getFilePath() << endl;
	Enginuity::setFilePath("Assets");
	cout << Enginuity::getFilePath() << endl;
	size_t size;
	Enginuity::getFileSize("game.txt", size);
	cout << size << endl;

	std::string contents;
	Enginuity::readFile("game.txt", contents);
	cout << contents << endl;

	Enginuity::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) 
	{
		cout << Enginuity::random(5, 10) << endl;
	}*/

	return 0;
}