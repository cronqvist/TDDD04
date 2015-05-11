#pragma once
#include "igameworldevent.h"
#include "game.h"

class GameWorldEventPlayerDied :
	public IGameWorldEvent
{
public:
	GameWorldEventPlayerDied();
	~GameWorldEventPlayerDied();
	void run();
	void setGame(Game* game);
private:
	Game* m_game;
};
