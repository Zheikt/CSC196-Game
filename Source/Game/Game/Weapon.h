#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

class Weapon : public Enginuity::Actor
{
public:
	Weapon(float speed, const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Model> model) :
		m_speed{ speed },
		Actor {transform, model} 
	{ m_lifespan = 2.0f; }

	void Update(float dt) override;

	void OnCollision(Actor* actor) override;
private:
	float m_speed = 0;
};