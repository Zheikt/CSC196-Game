#include "Actor.h"

void Actor::Draw(Enginuity::Renderer& renderer)
{
	m_model.Draw(renderer, m_transform);
}
