#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>

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
	Enginuity::seedRandom((unsigned int)time(nullptr));
	Enginuity::setFilePath("Assets");

	Enginuity::AudioSystem audioSystem;

	Enginuity::g_inputSystem.Initialize();
	audioSystem.Initialize();
	
	audioSystem.AddAudio("laser", "Laser.wav");
	audioSystem.AddAudio("explosion", "Explosion.wav");

	Enginuity::g_renderer.Initialize();
	Enginuity::g_renderer.CreateWindow("CSC196", 800, 600);

	float speed = 200.0f;
	constexpr float turnRate = Enginuity::DegreesToRadians(180);
	
	Enginuity::Model model;
	model.Load("ship.txt");

	Player player{ 200.0f, Enginuity::Pi, {{400, 300}, 0, 4}, model};

	std::vector<Enemy> enemies;
	for (size_t i = 0; i < 100; i++)
	{
		Enemy enemy{ 300.0f, Enginuity::Pi, {{Enginuity::random(800), Enginuity::random(600)}, Enginuity::randomf(Enginuity::TwoPi), 4 }, model};
		enemies.push_back(enemy);
	}

	//main game loop
	bool quit = false;
	while (!quit)
	{
		//Update Engine
		Enginuity::g_time.Tick();
		Enginuity::g_inputSystem.Update();
		audioSystem.Update();

		//0=L 1=M 2=R (Mouse buttons)
		if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !Enginuity::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			audioSystem.PlayOneShot("laser");
		}

		//update game
		player.Update(Enginuity::g_time.GetDeltaTime());
		for (auto& enemy : enemies) enemy.Update(Enginuity::g_time.GetDeltaTime());

		//draw game
		Enginuity::g_renderer.SetColor(0, 0, 0, 0);
		Enginuity::g_renderer.BeginFrame();

		Enginuity::g_renderer.SetColor(255, 255, 255, 0);

		player.Draw(Enginuity::g_renderer);
		for(auto& enemy : enemies) enemy.Draw(Enginuity::g_renderer);

		Enginuity::g_renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(500));
	}

	return 0;
}