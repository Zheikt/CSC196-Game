#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"
#include "Label.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "SpaceGame.h"
#include "Renderer/Emitter.h"

void Enemy::Update(float dt)
{
	Enginuity::Actor::Update(dt);

	Enginuity::vec2 forward = Enginuity::vec2{ 0, -1 }.Rotate((m_transform.rotation));
	m_transform.position += forward * m_speed * Enginuity::g_time.GetDeltaTime();
	m_transform.position.x = Enginuity::Wrap(m_transform.position.x, (float)Enginuity::g_renderer.GetWidth());
	m_transform.position.y = Enginuity::Wrap(m_transform.position.y, (float)Enginuity::g_renderer.GetHeight());
	
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		Enginuity::vec2 direction = player->m_transform.position - m_transform.position;

		//turn towards player
		float turnAngle = Enginuity::vec2::SignedAngle(forward, direction.Normalized());
		m_transform.rotation += turnAngle + m_turnRate;
		//check if viewing player
		if (std::fabs(turnAngle) < Enginuity::DegreesToRadians(30.0f))
		{
			Enginuity::Transform transform{m_transform.position, m_transform.rotation, 1};
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(m_weaponSpeed, transform, m_model);
			weapon->m_tag = "EnemyBullet";
			m_scene->Add(std::move(weapon));
			m_fireTimer = m_fireRate;
		}
	}

	//decrement fireTimer. If >=0, fire
	if ((m_fireTimer -= Enginuity::g_time.GetDeltaTime()) <= 0) 
	{
		Enginuity::Transform transform{m_transform.position, m_transform.rotation, 3};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(m_weaponSpeed, transform, m_model);
		weapon->m_tag = "EnemyBullet";
		weapon->SetImmunities({ "Enemy", "EnemyBullet", "Bonus" });
		m_scene->Add(std::move(weapon));
		m_fireTimer = m_fireRate;
	}
}

void Enemy::OnCollision(Actor* other)
{
	if (!Actor::ProcessCollision()) return;

	if ((other)->m_tag == "Player" || (other)->m_tag == "PlayerBullet")
	{
		m_health -= 1;
		if (m_health <= 0)
		{
			m_destroyed = true;
			m_game->AddPoints(m_pointValue);
			
			//Emitter
			Enginuity::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 0;
			data.angle = 0;
			data.angleRange = Enginuity::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = Enginuity::Color{ 255, 0, 0, 1 };
			std::unique_ptr<Enginuity::Emitter> emitter = std::make_unique<Enginuity::Emitter>(m_transform, data);
			emitter->m_lifespan = 0.5f;
			m_scene->Add(std::move(emitter));
			
			SpaceGame* game = dynamic_cast<SpaceGame*>(m_game);
			if (game)
			{
				std::unique_ptr<Label> label = std::make_unique<Label>(m_transform, game->GetSmallFont(), 10.0f, 0.5f);
				label->Create(Enginuity::g_renderer, std::to_string(m_pointValue), Enginuity::Color{255, 255, 255, 1});
				m_scene->Add(std::move(label));
			}

		}
	}
}
