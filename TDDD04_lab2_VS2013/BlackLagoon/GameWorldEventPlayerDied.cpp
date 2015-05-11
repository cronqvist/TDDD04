#include "GameWorldEventPlayerDied.h"

GameWorldEventPlayerDied::GameWorldEventPlayerDied()
	: m_game(0)
{
}

GameWorldEventPlayerDied::~GameWorldEventPlayerDied()
{
}

void GameWorldEventPlayerDied::run()
{
	if (m_game)
	{
		m_game->endGamePlay();
	}
	else
	{
		throw std::runtime_error("Game not set");
	}
}

void GameWorldEventPlayerDied::setGame(Game *game)
{
	m_game = game;
}