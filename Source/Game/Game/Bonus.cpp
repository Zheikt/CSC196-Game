#include "Bonus.h"

void Bonus::Draw(Enginuity::Renderer& renderer)
{
	Actor::Draw(renderer);
	m_valueText.Draw(renderer);
}

void Bonus::Create(Enginuity::Renderer& renderer, const Enginuity::Color& color)
{
	m_valueText.Create(renderer, std::to_string(m_value), color);
}