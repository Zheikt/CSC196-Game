#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"
#include <list>
#include <string>

class Weapon : public Enginuity::Actor
{
public:
	Weapon(float speed, const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Model> model) :
		m_speed{ speed },
		Actor {transform, model} 
	{ m_lifespan = 2.0f; }

	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

	void SetImmunities(std::list<std::string> labels) { m_immuneLabels = labels; }
private:
	float m_speed = 0;
	std::list<std::string> m_immuneLabels;
};