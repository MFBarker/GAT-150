#pragma once
#include "Framework/Game.h"
#include "Framework/Event.h"

class MyGame : public neu::Game
{
public:
	enum class gameState
	{
		Title_Screen,
		Level_Start,
		Game,
		Player_Dead,
		Game_Over
	};

public:
	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(neu::Renderer& renderer) override;

	void OnAddPoints(const neu::Event& event);
	void OnPlayerDead(const neu::Event& event);

private:
	gameState m_gameState = gameState::Title_Screen;
	float m_stateTimer = 0;
	int m_lives = 3;
};