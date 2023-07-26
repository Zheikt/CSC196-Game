#include "Label.h"
#include "Renderer/Renderer.h"

void Label::Draw(Enginuity::Renderer& renderer)
{
	Text::Draw(renderer, (int)m_transform.position.x, (int)m_transform.position.y);
}
