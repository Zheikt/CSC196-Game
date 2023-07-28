#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

class Player : public Enginuity::Actor
{
public:
	Player(float speed, float turnRate, const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Model> model)
		: Actor{ transform, model }, m_speed(speed), m_turnRate(turnRate)
	{}

	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 20;

	bool m_burstActive;
	float m_burstTimeRemaining = 5.0f;
};