#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"


class SpaceGame : public Enginuity::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};
public:
	virtual bool Init() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(Enginuity::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;

	std::shared_ptr<Enginuity::Font> m_font;
	std::unique_ptr<Enginuity::Text> m_scoreText;
	std::unique_ptr<Enginuity::Text> m_titleText;
};