#include "Player.h"
#include "Weapon.h"
#include "BurstWeapon.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"
#include "SpaceGame.h"

void Player::Update(float dt)
{
	Enginuity::Actor::Update(dt);

	if (m_burstActive) m_burstTimeRemaining -= dt;

	Enginuity::vec2 direction;
	float rotate = 0;

	if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * dt;

	float thrust = 0;
	if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	Enginuity::vec2 forward = Enginuity::vec2{ 0, -1 }.Rotate((m_transform.rotation));
	AddForce(forward * m_speed * thrust);

	//m_transform.position += forward * m_speed * thrust * dt;
	m_transform.position.x = Enginuity::Wrap(m_transform.position.x, (float)Enginuity::g_renderer.GetWidth());
	m_transform.position.y = Enginuity::Wrap(m_transform.position.y, (float)Enginuity::g_renderer.GetHeight());

	if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !Enginuity::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		if (m_burstActive) 
		{
			Enginuity::Transform transform1{m_transform.position, m_transform.rotation, 3};
			std::unique_ptr<BurstWeapon> weapon = std::make_unique<BurstWeapon>(400.0f, transform1, Enginuity::g_manager.Get("bullet.txt"));
			weapon->m_tag = "PlayerBullet";
			weapon->SetImmunities({ "Player", "PlayerBullet", "Bonus" });
			m_scene->Add(std::move(weapon));
		}
		else
		{
			Enginuity::Transform transform1{m_transform.position, m_transform.rotation + Enginuity::DegreesToRadians(10.0f), 3};
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1, Enginuity::g_manager.Get("bullet.txt"));
			weapon->m_tag = "PlayerBullet";
			weapon->SetImmunities({ "Player", "PlayerBullet", "Bonus"});
			m_scene->Add(std::move(weapon));

			Enginuity::Transform transform2{m_transform.position, m_transform.rotation - Enginuity::DegreesToRadians(10.0f), 3};
			std::unique_ptr<Weapon> weapon2 = std::make_unique<Weapon>(500.0f, transform2, Enginuity::g_manager.Get("bullet.txt"));
			weapon2->m_tag = "PlayerBullet";
			weapon2->m_lifespan = 0.75f;
			weapon2->SetImmunities({ "Player", "PlayerBullet", "Bonus"});
			m_scene->Add(std::move(weapon2));
		}
		
	}

	if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) Enginuity::g_time.SetTimeScale(0.5f);
	else Enginuity::g_time.SetTimeScale(1.0f);
}

void Player::OnCollision(Actor* other)
{
	if (!Actor::ProcessCollision()) return;
	if (other->m_tag == "BurstCollectible")
	{
		m_burstActive = true;
		m_burstTimeRemaining = 5.0f;
	}
	if (other->m_tag != "Player" && other->m_tag != "PlayerBullet" && other->m_tag != "Bonus" && other->m_tag != "BurstCollectible")
	{
		m_health -= 1;
		if (m_health <= 0 && !m_destroyed) 
		{
			m_destroyed = true;
			m_game->SetLives(m_game->GetLives() - 1);
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
		}
	}
}
