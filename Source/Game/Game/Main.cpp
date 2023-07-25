#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

#include "SpaceGame.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <memory>

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
		m_pos += m_vel * Enginuity::g_time.GetDeltaTime();

		if (m_pos.x > width) m_pos.x = 0;
		if (m_pos.x < 0) m_pos.x = (float)width;
		if (m_pos.y > height) m_pos.y = 0;
		if (m_pos.y < 0) m_pos.y = (float)height;
	}

	void Update()
	{
		m_pos += m_vel * Enginuity::g_time.GetDeltaTime();

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
	Enginuity::MemoryTracker::Initialize();
	Enginuity::seedRandom((unsigned int)time(nullptr));
	Enginuity::setFilePath("Assets");

	Enginuity::g_renderer.Initialize();
	Enginuity::g_renderer.CreateWindow("CSC196", 800, 600);

	Enginuity::g_inputSystem.Initialize();
	Enginuity::g_audioSystem.Initialize();

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Init();

	//main game loop
	bool quit = false;
	while (!quit)
	{
		//Update Engine
		Enginuity::g_time.Tick();
		Enginuity::g_inputSystem.Update();
		Enginuity::g_audioSystem.Update();

		//0=L 1=M 2=R (Mouse buttons)
		if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) 
		{
			quit = true;
		}

		if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !Enginuity::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			Enginuity::g_audioSystem.PlayOneShot("laser");
		}

		//update game
		game->Update(Enginuity::g_time.GetDeltaTime());

		//draw game
		Enginuity::g_renderer.SetColor(0, 0, 0, 0);
		Enginuity::g_renderer.BeginFrame();

		Enginuity::g_renderer.SetColor(255, 255, 255, 0);

		game->Draw(Enginuity::g_renderer);

		Enginuity::g_renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(500));
	}

	return 0;
}