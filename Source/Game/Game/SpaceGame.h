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
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};
public:
	virtual bool Init() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(Enginuity::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

	std::shared_ptr<Enginuity::Font> GetSmallFont() const { return m_fontSmall; }
	std::shared_ptr<Enginuity::Font> GetNormalFont() const { return m_fontNormal; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;

	float m_gameTimer = 0;

	float m_stateTimer = 0;

	float m_recordTime = 0;

	std::shared_ptr<Enginuity::Font> m_fontNormal;
	std::shared_ptr<Enginuity::Font> m_fontSmall;
	std::shared_ptr<Enginuity::Font> m_fontLarge;
	std::unique_ptr<Enginuity::Text> m_scoreText;
	std::unique_ptr<Enginuity::Text> m_titleText;
	std::unique_ptr<Enginuity::Text> m_gameOverText;
	std::unique_ptr<Enginuity::Text> m_timerText;
	std::unique_ptr<Enginuity::Text> m_livesText;
	std::unique_ptr<Enginuity::Text> m_newRecordText;
};