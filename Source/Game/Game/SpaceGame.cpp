#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Emitter.h"

bool SpaceGame::Init()
{
	//Init Font/Text
	m_font = std::make_shared<Enginuity::Font>("VCR_OSD_MONO.ttf", 24);
	m_scoreText = std::make_unique<Enginuity::Text>(m_font);
	m_scoreText->Create(Enginuity::g_renderer, "SCORE 0000", Enginuity::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<Enginuity::Text>(m_font);
	m_titleText->Create(Enginuity::g_renderer, "ASTEROIDS", Enginuity::Color{ 1, 1, 1, 1 });

	m_gameOverText = std::make_unique<Enginuity::Text>(m_font);
	m_gameOverText->Create(Enginuity::g_renderer, "GAME OVER", Enginuity::Color{ 1, 1, 1, 1 });

	m_timerText = std::make_unique<Enginuity::Text>(m_font);
	m_timerText->Create(Enginuity::g_renderer, "TIMER", Enginuity::Color{ 1, 1, 1, 1 });

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

		std::unique_ptr<Player> player = std::make_unique<Player>(20, Enginuity::Pi, Enginuity::Transform{ {400, 300}, 0, 8 }, Enginuity::g_manager.Get("player.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9f);
		m_scene->Add(std::move(player));

		Enginuity::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = Enginuity::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = Enginuity::Color{ 1, 0, 0, 1 };
		Enginuity::Transform transform{ { Enginuity::g_inputSystem.GetMousePosition() }, 0, 1 };
		std::unique_ptr<Enginuity::Emitter> emitter = std::make_unique<Enginuity::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));

		m_state = eState::Game;
		break;
	}
	case SpaceGame::eState::Game:
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(300.0f, Enginuity::Pi, Enginuity::Transform{{Enginuity::random(800), Enginuity::random(600)}, Enginuity::randomf(Enginuity::TwoPi), 3 }, Enginuity::g_manager.Get("enemy.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) 
		{
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(Enginuity::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
	m_timerText->Create(Enginuity::g_renderer, std::to_string(m_gameTimer), { 1, 1, 1, 1 });

	m_scene->Update(dt);
}

void SpaceGame::Draw(Enginuity::Renderer& renderer)
{
	if (m_state == eState::Title) 
	{
		m_titleText->Draw(renderer, 400, 300);
	}
	else if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 350, 300);
	}

	m_timerText->Draw(renderer, 400, 20);
	m_scoreText->Draw(renderer, 40, 20);
	m_scene->Draw(renderer);
}
