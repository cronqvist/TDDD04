#include "GameWorldEventLevelUp.h"

GameWorldEventLevelUp::GameWorldEventLevelUp()
	: m_game(0)
{
}

GameWorldEventLevelUp::~GameWorldEventLevelUp()
{
}

void GameWorldEventLevelUp::run()
{
	if (m_game)
	{
		m_game->levelUp();
	}
	else
	{
		throw std::runtime_error("Game not set");
	}
}

void GameWorldEventLevelUp::setGame(Game *game)
{
	m_game = game;
}