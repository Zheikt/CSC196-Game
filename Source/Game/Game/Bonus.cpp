#include "Bonus.h"
#include "SpaceGame.h"

void Bonus::Update(float dt)
{
	Enginuity::Actor::Update(dt);

	Enginuity::vec2 forward = Enginuity::vec2{ 0, -1 }.Rotate((m_transform.rotation));
	m_transform.position += forward * m_speed * Enginuity::g_time.GetDeltaTime();
	m_transform.position.x = Enginuity::Wrap(m_transform.position.x, (float)Enginuity::g_renderer.GetWidth());
	m_transform.position.y = Enginuity::Wrap(m_transform.position.y, (float)Enginuity::g_renderer.GetHeight());
}

void Bonus::OnCollision(Actor* other)
{
	if (other->m_tag == "Player")
	{
		m_destroyed = true;
		m_game->AddPoints(200);
	}
}
