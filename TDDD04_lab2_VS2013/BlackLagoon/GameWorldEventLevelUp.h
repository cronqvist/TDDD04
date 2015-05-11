#pragma once
#include "igameworldevent.h"
#include "game.h"

class GameWorldEventLevelUp :
	public IGameWorldEvent
{
public:
	GameWorldEventLevelUp();
	~GameWorldEventLevelUp();
	void run();
	void setGame(Game* game);
private:
	Game* m_game;
};
