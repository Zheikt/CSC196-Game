#include "BurstWeapon.h"
#include "Renderer/ModelManager.h"
#include "Framework/Scene.h"


void BurstWeapon::Update(float dt)
{
	Weapon::Update(dt);

	if (m_destroyed)
	{
		GenerateBurst();
	}
}

void BurstWeapon::OnCollision(Actor* other)
{
	Weapon::OnCollision(other);

	if (!Actor::ProcessCollision()) return;

	if (m_destroyed)
	{
 		GenerateBurst();
	}
}

void BurstWeapon::GenerateBurst()
{
	for (int iter = 1; iter <= 8; iter++)
	{
		Enginuity::Transform transform1{m_transform.position, (float)(Enginuity::TwoPi / iter), 2};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1, Enginuity::g_manager.Get("bullet.txt"));
		weapon->m_tag = "PlayerBullet";
		weapon->SetImmunities({ "Player", "PlayerBullet", "Bonus" });
		m_scene->Add(std::move(weapon));
	}
}
