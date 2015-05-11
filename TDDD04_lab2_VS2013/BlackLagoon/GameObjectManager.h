#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "stdafx.h"
#include "IGameObjectManager.h"
#include "IGameObjectFactory.h"
#include "SpecialGameObject.h"

class GameObject;
class GameObjectFactory;
class Player;
class Shot;

class GameObjectManager : public IGameObjectManager
{
public:
	GameObjectManager(IGameObjectFactory* gof);
	~GameObjectManager();

public:
	virtual GameObject* addEnemy(int objType);
	void removeEnemy(std::vector<GameObject*>::iterator it);
	virtual void removeEnemy(int i);
	
	virtual SpecialGameObject* addSpecialObject(int objType);
	void removeSpecialObject(std::vector<SpecialGameObject*>::iterator it);
	virtual void removeSpecialObject(int i);

	virtual Player* addPlayer(IInputDevice* input);
	
	virtual Shot* addPlayerShot();
	virtual Shot* getPlayerShot(int index);
	virtual int getPlayerShotsInUse();
	virtual void removePlayerShot(int index);
	
	virtual Shot* addEnemyShot();
	virtual Shot* getEnemyShot(int index);
	virtual int getEnemyShotsInUse();
	virtual void removeEnemyShot(int index);

	virtual Player* getPlayer();
	virtual void reset();
	virtual void clearForNewLevel();

	void render(Rect& cameraView);

	virtual std::vector<GameObject*>& Enemies();
	virtual std::vector<GameObject*>& ActiveEnemies();
	virtual std::vector<SpecialGameObject*>& SpecialObjects();
	
private:

	std::vector<GameObject*> m_enemies;
	std::vector<GameObject*> m_activeEnemies;
	
	std::vector<SpecialGameObject*> m_specialObjects;

	std::vector<Shot*> m_enemyShots;
	std::vector<Shot*> m_playerShots;
	int m_playerShotsInUse;
	int m_enemyShotsInUse;

	Player* m_player;

	IGameObjectFactory* m_gof;

};
#endif