#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

void Player::Update(float dt)
{
	Enginuity::vec2 direction;
	float rotate = 0;

	if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * dt;

	float thrust = 0;
	if (Enginuity::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	Enginuity::vec2 forward = Enginuity::vec2{ 0, -1 }.Rotate((m_transform.rotation));
	m_transform.position += forward * m_speed * thrust * dt;
	m_transform.position.x = Enginuity::Wrap(m_transform.position.x, (float)Enginuity::g_renderer.GetWidth());
	m_transform.position.y = Enginuity::Wrap(m_transform.position.y, (float)Enginuity::g_renderer.GetHeight());
}
