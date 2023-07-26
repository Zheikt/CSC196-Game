#pragma once
#include "Framework/Actor.h"

class Bonus : public Enginuity::Actor 
{
public:
	Bonus() = default;
	Bonus(float speed, float turnRate, const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Model> model)
		: Actor{ transform, model }, m_speed(speed), m_turnRate(turnRate) 
	{
		m_lifespan = 3.0f;
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

private:
	float m_speed;
	float m_turnRate;
};