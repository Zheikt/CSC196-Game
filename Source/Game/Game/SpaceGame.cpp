#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Init()
{
	//Init Font/Text
	m_font = std::make_shared<Enginuity::Font>("VCR_OSD_MONO.ttf", 24);
	m_scoreText = std::make_unique<Enginuity::Text>(m_font);
	m_scoreText->Create(Enginuity::g_renderer, "SCORE 0000", Enginuity::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<Enginuity::Text>(m_font);
	m_titleText->Create(Enginuity::g_renderer, "ASTEROIDS", Enginuity::Color{ 1, 1, 1, 1 });

	//load audio
	Enginuity::g_audioSystem.AddAudio("laser", "Laser.wav");

	m_scene = std::make_unique<Enginuity::Scene>();

	return false;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) 
		{
			m_state = eState::StartGame;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel:
	{
		m_scene->RemoveAll();

		std::unique_ptr<Player> player = std::make_unique<Player>(200.f, Enginuity::Pi, Enginuity::Transform{ {400, 300}, 0, 4 }, Enginuity::g_manager.Get("ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		m_scene->Add(std::move(player));

		m_state = eState::Game;
		break;
	}
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(300.0f, Enginuity::Pi, Enginuity::Transform{{Enginuity::random(800), Enginuity::random(600)}, Enginuity::randomf(Enginuity::TwoPi), 3 }, Enginuity::g_manager.Get("ship.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
		break;
	case SpaceGame::eState::PlayerDead:
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::GameOver:
		break;
	default:
		break;
	}

	m_scoreText->Create(Enginuity::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });

	m_scene->Update(dt);
}

void SpaceGame::Draw(Enginuity::Renderer& renderer)
{
	if (m_state == eState::Title) 
	{
		m_titleText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 20);
	m_scene->Draw(renderer);
}
