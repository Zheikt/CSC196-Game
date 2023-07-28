#pragma once
#include "Collectible.h"
#include "Label.h"
#include <string>

class Renderer;

class Bonus : public Collectible
{
public:
	Bonus() = default;
	Bonus(float speed, const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Model> model, std::shared_ptr<Enginuity::Font> font, const int value)
		: Collectible{ speed, transform, model, value }
	{
		m_lifespan = 3.0f;
		Enginuity::Transform transform2 = transform;
		transform2.position.x -= 13;
		transform2.position.y -= 8;
		m_valueText = Label{ transform2, font, speed, m_lifespan };
	}

	void Draw(Enginuity::Renderer& renderer) override;

	void Create(Enginuity::Renderer& renderer, const Enginuity::Color& color);

private:
	Label m_valueText;
};