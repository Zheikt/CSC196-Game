#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Bonus.h"

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
	m_fontNormal = std::make_shared<Enginuity::Font>("VCR_OSD_MONO.ttf", 24);
	m_fontLarge = std::make_shared<Enginuity::Font>("VCR_OSD_MONO.ttf", 36);
	m_fontSmall = std::make_shared<Enginuity::Font>("VCR_OSD_MONO.ttf", 16);
	m_scoreText = std::make_unique<Enginuity::Text>(m_fontNormal);
	m_scoreText->Create(Enginuity::g_renderer, "SCORE 0000", Enginuity::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<Enginuity::Text>(m_fontLarge);
	m_titleText->Create(Enginuity::g_renderer, "COSMIC KILLER COMPETITION", Enginuity::Color{ 1, 1, 1, 1 });

	m_gameOverText = std::make_unique<Enginuity::Text>(m_fontLarge);
	m_gameOverText->Create(Enginuity::g_renderer, "GAME OVER", Enginuity::Color{ 1, 1, 1, 1 });

	m_timerText = std::make_unique<Enginuity::Text>(m_fontNormal);
	m_timerText->Create(Enginuity::g_renderer, "TIMER", Enginuity::Color{ 1, 1, 1, 1 });

	m_livesText = std::make_unique<Enginuity::Text>(m_fontNormal);
	m_livesText->Create(Enginuity::g_renderer, "LIVES", Enginuity::Color{ 1, 1, 1, 1 });

	m_newRecordText = std::make_unique<Enginuity::Text>(m_fontLarge);
	m_newRecordText->Create(Enginuity::g_renderer, "NEW RECORD!!!", Enginuity::Color{ 1, 1, 1, 1 });

	//load audio
	Enginuity::g_audioSystem.AddAudio("laser", "Laser.wav");
	Enginuity::g_audioSystem.AddAudio("title_music", "OutThere.ogg");
	Enginuity::g_audioSystem.AddAudio("game_music", "through space.ogg");

	m_scene = std::make_unique<Enginuity::Scene>();
	
	//Load record
	std::string fileTime;
	m_recordTime = Enginuity::readFile("TimeRecord.txt", fileTime) ? std::stof(fileTime) : 0;
	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
	{
		if (!Enginuity::g_audioSystem.IsPlaying("title_music")) Enginuity::g_audioSystem.PlayLoop("title_music");
		m_score = 0;
		m_gameTimer = m_recordTime;
		m_lives = 3;
		if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;
	}
	case SpaceGame::eState::StartGame:
		Enginuity::g_audioSystem.StopLoop("title_music");
		Enginuity::g_audioSystem.PlayLoop("game_music");
		m_score = 0;
		m_lives = 3;
		m_gameTimer = 0;
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
		data.burstCount = 300;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = Enginuity::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = Enginuity::Color{ 1, 1, 1, 1 };
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

		if (m_score >= 1000)
		{
			m_state = eState::PlayerDeadStart;
			m_lives = 0;
			break;
		}

		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(300.0f, Enginuity::DegreesToRadians(85), 400.0f, Enginuity::Transform{{Enginuity::random(800), Enginuity::random(600)}, Enginuity::randomf(Enginuity::TwoPi), 3 }, Enginuity::g_manager.Get("enemy.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));

			if (Enginuity::randomf() <= 0.1f)
			{
				//Speedster enemy
				std::unique_ptr<Enemy> speedster = std::make_unique<Enemy>(450.0f, Enginuity::DegreesToRadians(-35), 700.0f, Enginuity::Transform{{Enginuity::random(800), Enginuity::random(600)}, Enginuity::randomf(Enginuity::TwoPi), 8 }, Enginuity::g_manager.Get("speedster.txt"));
				speedster->m_tag = "Enemy";
				speedster->m_game = this;
				m_scene->Add(std::move(speedster));
			}

			if (Enginuity::randomf() <= 0.4f)
			{
				if (Enginuity::randomf() <= 0.3f)
				{
					std::unique_ptr<Collectible> burst = std::make_unique<Collectible>(0, Enginuity::Transform{{Enginuity::random(800), Enginuity::random(600)}, 0, 7 }, Enginuity::g_manager.Get("burst.txt"), 100);
					burst->m_tag = "BurstCollectible";
					burst->m_game = this;
					m_scene->Add(std::move(burst));
				}
				else
				{
					std::unique_ptr<Bonus> bonus = std::make_unique<Bonus>(0, Enginuity::Transform{{Enginuity::random(800), Enginuity::random(600)}, 0, 7 }, Enginuity::g_manager.Get("bonus.txt"), m_fontSmall, Enginuity::random(1, 10) * 100);
					bonus->m_tag = "Bonus";
					bonus->m_game = this;
					bonus->Create(Enginuity::g_renderer, Enginuity::Color{ 1,1,1,1 });
					m_scene->Add(std::move(bonus));
				}
				
			}
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
		Enginuity::g_audioSystem.StopLoop("game_music");
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) 
		{
			if (m_score >= 1000) 
			{
				//save Fastest Time
				std::string currentTime = std::to_string(m_gameTimer);
				std::string recordTime;
				Enginuity::readFile("TimeRecord.txt", recordTime);
				float recTime = std::stof(recordTime == "" ? currentTime : recordTime);
				if (recTime >= m_gameTimer)
				{
					Enginuity::saveFile("TimeRecord.txt", currentTime);
					m_recordTime = m_gameTimer;
				}
				
			}
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(Enginuity::g_renderer, "SCORE: " + std::to_string(m_score), {1, 1, 1, 1});
	m_timerText->Create(Enginuity::g_renderer, std::to_string(m_gameTimer), { 1, 1, 1, 1 });
	m_livesText->Create(Enginuity::g_renderer, "LIVES: " + std::to_string(m_lives), {1, 1, 1, 1});

	if(m_state != eState::GameOver) m_scene->Update(dt);
}

void SpaceGame::Draw(Enginuity::Renderer& renderer)
{
	if (m_state == eState::Title) 
	{
		m_titleText->Draw(renderer, 150, 300);
	}
	else if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 350, 300);
     		if (m_score >= 1000 && m_recordTime >= m_gameTimer) m_newRecordText->Draw(renderer, 350, 160);
	}

	m_timerText->Draw(renderer, 350, 20);
	m_scoreText->Draw(renderer, 40, 20);
	m_livesText->Draw(renderer, 600, 20);
	m_scene->Draw(renderer);
}
