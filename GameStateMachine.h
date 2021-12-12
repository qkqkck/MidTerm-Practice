#pragma once
#include "GameState.h"
class GameStateMachine
{
public:
	void changeState(GameState* pState);
	void pushState(GameState* pState);
	void PopupState(GameState* pState);
	void popState();
	virtual void update();
	virtual void render();

protected:
	std::vector<GameState*> m_gameStates;

private:
	GameState* m_currentState;
	GameState* m_prevState;
};