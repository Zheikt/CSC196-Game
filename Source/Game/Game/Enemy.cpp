#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "SpaceGame.h"

void Enemy::Update(float dt)
{
	Enginuity::Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		Enginuity::vec2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + Enginuity::HalfPi;
	}

	Enginuity::vec2 forward = Enginuity::vec2{ 0, -1 }.Rotate((m_transform.rotation));
	m_transform.position += forward * m_speed * Enginuity::g_time.GetDeltaTime();
	m_transform.position.x = Enginuity::Wrap(m_transform.position.x, (float)Enginuity::g_renderer.GetWidth());
	m_transform.position.y = Enginuity::Wrap(m_transform.position.y, (float)Enginuity::g_renderer.GetHeight());

	//decrement fireTimer. If >=0, fire
	if ((m_fireTimer -= Enginuity::g_time.GetDeltaTime()) <= 0) 
	{
		Enginuity::Transform transform{m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
		weapon->m_tag = "Player";
		m_scene->Add(std::move(weapon));
		m_fireTimer = m_fireRate;
	}
}

void Enemy::OnCollision(Actor* other)
{
	if ((other)->m_tag == "Player")
	{
		m_game->AddPoints(100);
		m_health -= 1;
		if(m_health <= 0) m_destroyed = true;
		
	}
}
