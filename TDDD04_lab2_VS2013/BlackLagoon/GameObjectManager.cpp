#include "GameObjectManager.h"

using std::vector;

GameObjectManager::GameObjectManager(IGameObjectFactory* gof) :
	m_gof(gof),
	m_playerShotsInUse(0),
	m_enemyShotsInUse(0),
	m_player(0)
{
}

GameObjectManager::~GameObjectManager()
{
	reset();
}

GameObject* GameObjectManager::addEnemy(int objType)
{
	GameObject* go =  m_gof->getEnemy(objType);
	m_enemies.push_back(go);
	return go;
}

void GameObjectManager::removeEnemy(std::vector<GameObject*>::iterator it)
{
	m_enemies.erase(it);
}

void GameObjectManager::removeEnemy(int i)
{
	m_gof->release(m_enemies[i]);
	std::swap(m_enemies[i], m_enemies[m_enemies.size()-1]);
	m_enemies.pop_back();
}

SpecialGameObject* GameObjectManager::addSpecialObject(int objType)
{
	SpecialGameObject* sgo = m_gof->getSpecialObject(objType);
	m_specialObjects.push_back(sgo);
	return sgo;
}

void GameObjectManager::removeSpecialObject(std::vector<SpecialGameObject*>::iterator it)
{
	m_specialObjects.erase(it);
}

void GameObjectManager::removeSpecialObject(int i)
{
	m_gof->release(m_specialObjects[i]);
	std::swap(m_specialObjects[i], m_specialObjects[m_specialObjects.size()-1]);
	m_specialObjects.pop_back();
}


Player* GameObjectManager::addPlayer(IInputDevice* input)
{
	m_player = m_gof->getPlayer(input);
	return m_player;
}

Player* GameObjectManager::getPlayer()
{
	return m_player;
}

Shot* GameObjectManager::addPlayerShot()
{
	if (m_playerShotsInUse == m_playerShots.size())
		m_playerShots.push_back(m_gof->getPlayerShot());

	
	// 0-index, hence increment after read of value
	return m_playerShots[m_playerShotsInUse++];
}

Shot* GameObjectManager::getPlayerShot(int index)
{
	return m_playerShots[index];
}

int GameObjectManager::getPlayerShotsInUse()
{
	return m_playerShotsInUse;
}

void GameObjectManager::removePlayerShot(int index)
{
	// reduce playerShotsIn use and now the new value can be used since 0-index
	std::swap(m_playerShots[index], m_playerShots[--m_playerShotsInUse]);
}

Shot* GameObjectManager::addEnemyShot()
{
	if (m_enemyShotsInUse == m_enemyShots.size())
		m_enemyShots.push_back(m_gof->getEnemyShot());
	
	// 0-index, hence increment after read of value
	return m_enemyShots[m_enemyShotsInUse++];
}


Shot* GameObjectManager::getEnemyShot(int index)
{
	return m_enemyShots[index];
}

int GameObjectManager::getEnemyShotsInUse()
{
	return m_enemyShotsInUse;
}

void GameObjectManager::removeEnemyShot(int index)
{
	// reduce enemyShotsIn use and now the new value can be used since 0-index
	std::swap(m_enemyShots[index], m_enemyShots[--m_enemyShotsInUse]);
}

void GameObjectManager::reset()
{
	m_gof->release(m_player);

	for (vector<GameObject*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++)
	{
		m_gof->release((*it));
	}
	m_enemies.clear();

	for (vector<SpecialGameObject*>::iterator it = m_specialObjects.begin(); it != m_specialObjects.end(); it++)
	{
		m_gof->release((*it));
	}
	m_specialObjects.clear();

	for (vector<Shot*>::iterator it = m_enemyShots.begin(); it != m_enemyShots.end(); it++)
	{
		m_gof->release((*it));
	}
	m_enemyShots.clear();
	m_enemyShotsInUse = 0;

	for (vector<Shot*>::iterator it = m_playerShots.begin(); it != m_playerShots.end(); it++)
	{
		m_gof->release((*it));
	}
	m_playerShots.clear();
	m_playerShotsInUse = 0;
	
}

void GameObjectManager::clearForNewLevel()
{
	for (vector<GameObject*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++)
	{
		m_gof->release((*it));
	}
	m_enemies.clear();

	for (vector<SpecialGameObject*>::iterator it = m_specialObjects.begin(); it != m_specialObjects.end(); it++)
	{
		m_gof->release((*it));
	}
	m_specialObjects.clear();


	m_enemyShotsInUse = 0;
	m_playerShotsInUse = 0;
}

void GameObjectManager::render(Rect& cameraView)
{
	// Player
	if (m_player)
		m_player->render(cameraView);

	// Enemies
	for (vector<GameObject*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++)
	{
		// Render only active enemies
		if ((*it)->getActive())
			(*it)->render(cameraView);
	}

	// Special objects - render all since they are so few
	for (vector<SpecialGameObject*>::iterator it = m_specialObjects.begin(); it != m_specialObjects.end(); it++)
	{
		(*it)->render(cameraView);
	}

	// Enemy shots - only active shots in the vector
	for (int i = 0; i < m_enemyShotsInUse; i++)
	{	
		m_enemyShots[i]->render(cameraView);
	}

	// Player shots - only active shots in the vector
	for (int i = 0; i < m_playerShotsInUse; i++)
	{
		m_playerShots[i]->render(cameraView);
	}
}

std::vector<GameObject*>& GameObjectManager::Enemies()
{
	return m_enemies;
}

std::vector<GameObject*>& GameObjectManager::ActiveEnemies()
{
	return m_activeEnemies;
}

std::vector<SpecialGameObject*>& GameObjectManager::SpecialObjects()
{
	return m_specialObjects;
}
	