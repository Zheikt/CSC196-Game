#pragma once
#include "Framework/Actor.h"
#include <string>

class Renderer;

class Collectible : public Enginuity::Actor
{
public:
	Collectible() = default;
	Collectible(float speed, const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Model> model, const int value)
		: Actor{ transform, model }, m_speed(speed), m_value(value)
	{
		m_lifespan = 4.0f;
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

protected:
	float m_speed;
	int m_value;
};