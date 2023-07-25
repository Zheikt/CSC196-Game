#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

void Weapon::Update(float dt)
{
	Enginuity::Actor::Update(dt);

	Enginuity::vec2 forward = Enginuity::vec2{ 0, -1 }.Rotate((m_transform.rotation));
	m_transform.position += forward * m_speed * Enginuity::g_time.GetDeltaTime();
	m_transform.position.x = Enginuity::Wrap(m_transform.position.x, (float)Enginuity::g_renderer.GetWidth());
	m_transform.position.y = Enginuity::Wrap(m_transform.position.y, (float)Enginuity::g_renderer.GetHeight());
}

void Weapon::OnCollision(Actor* other)
{
	if (other->m_tag != m_tag)
	{
		m_destroyed = true;
	}
}
