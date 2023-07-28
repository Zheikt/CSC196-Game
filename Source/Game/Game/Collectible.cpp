#include "Collectible.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Label.h"
#include "Framework/Scene.h"

void Collectible::Update(float dt)
{
	Enginuity::Actor::Update(dt);

	Enginuity::vec2 forward = Enginuity::vec2{ 0, -1 }.Rotate((m_transform.rotation));
	m_transform.position += forward * m_speed * Enginuity::g_time.GetDeltaTime();
	m_transform.position.x = Enginuity::Wrap(m_transform.position.x, (float)Enginuity::g_renderer.GetWidth());
	m_transform.position.y = Enginuity::Wrap(m_transform.position.y, (float)Enginuity::g_renderer.GetHeight());
}

void Collectible::OnCollision(Actor* other)
{
	if (!Actor::ProcessCollision()) return;

	if (other->m_tag == "Player")
	{
		m_destroyed = true;
		m_game->AddPoints(m_value);

		SpaceGame* game = dynamic_cast<SpaceGame*>(m_game);
		if (game)
		{
			std::unique_ptr<Label> label = std::make_unique<Label>(m_transform, game->GetSmallFont(), 10.0f, 0.5f);
			label->Create(Enginuity::g_renderer, std::to_string(m_value), Enginuity::Color{255, 255, 255, 1});
			m_scene->Add(std::move(label));
		}
	}


}