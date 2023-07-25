#include "Actor.h"

namespace Enginuity
{
	void Actor::Update(float dt) {
		if (m_lifespan != -1.0f) 
		{
			m_lifespan -= dt;

			if (m_lifespan <= 0) {
				m_destroyed = true;
			}
		}
	}

	void Actor::Draw(Enginuity::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}