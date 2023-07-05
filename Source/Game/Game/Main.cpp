#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
	Enginuity::Renderer renderer;

	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	while (true) 
	{
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//draw
		renderer.SetColor(Enginuity::random(256), Enginuity::random(256), Enginuity::random(256), Enginuity::random(256));

		for (size_t i = 0; i < 100; i++)
		{
			//renderer.DrawPoint(Enginuity::random(renderer.GetWidth()), Enginuity::random(renderer.GetHeight()));
			renderer.DrawLine(Enginuity::random(renderer.GetWidth()), Enginuity::random(renderer.GetHeight()), Enginuity::random(renderer.GetWidth()), Enginuity::random(renderer.GetHeight()));
		}

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
}