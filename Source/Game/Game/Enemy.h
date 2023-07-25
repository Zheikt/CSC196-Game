#pragma once
#include "Renderer/Model.h"
#include "Framework/Actor.h"

class Enemy : public Enginuity::Actor
{
public:
	Enemy(float speed, float turnRate, const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Model> model)
		: Actor{ transform, model }, m_speed(speed), m_turnRate(turnRate)
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 5;
	float m_fireRate = 0;
	float m_fireTimer = 0;
};