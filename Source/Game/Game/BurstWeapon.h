#pragma once
#include "Weapon.h"

class BurstWeapon : public Weapon
{
public:
	BurstWeapon(float speed, const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Model> model) :
		Weapon{speed, transform, model}
	{
		m_lifespan = 1.5f;
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	void GenerateBurst();
};