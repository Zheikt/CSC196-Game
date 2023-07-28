#pragma once
#include "Framework/Actor.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

class Label : public Enginuity::Text, public Enginuity::Actor
{
	class Renderer;

public:
	Label() = default;
	Label(const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Font> font, const float speed, const float lifespan)
		: Actor{ transform }, Text{ font }, m_speed{ speed }
	{
		m_lifespan = lifespan;
	}

	void Draw(Enginuity::Renderer& renderer);
	void Update(float dt) override;

private:
	float m_speed = 0;
};