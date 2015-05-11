#pragma once

#include "SpecialGameObject.h"
#include "Player.h"
#include "Shot.h"
#include "GameObject.h"
#include "IInputDevice.h"
#include <vector>

class Player;
class SpecialGameObject;

class IGameObjectManager
{
public:
	virtual ~IGameObjectManager(){};

	virtual GameObject* addEnemy(int objType) = 0;
	virtual void removeEnemy(std::vector<GameObject*>::iterator it) = 0;
	virtual void removeEnemy(int i) = 0;
	virtual SpecialGameObject* addSpecialObject(int objType) = 0;
	virtual void removeSpecialObject(std::vector<SpecialGameObject*>::iterator it) = 0;
	virtual void removeSpecialObject(int i) = 0;
	virtual Player* addPlayer(IInputDevice *input) = 0;
	virtual Shot* addPlayerShot() = 0;
	virtual Shot* getPlayerShot(int index) = 0;
	virtual int getPlayerShotsInUse() = 0;
	virtual void removePlayerShot(int index) = 0;
	virtual Shot* addEnemyShot() = 0;
	virtual Shot* getEnemyShot(int index) = 0;
	virtual int getEnemyShotsInUse() = 0;
	virtual void removeEnemyShot(int index) = 0;
	virtual Player* getPlayer() = 0;
	virtual void reset() = 0;
	virtual void clearForNewLevel() = 0;
	virtual void render(Rect &cameraView) = 0;
	virtual std::vector<GameObject*>& Enemies() = 0;
	virtual std::vector<GameObject*>& ActiveEnemies() = 0;
	virtual std::vector<SpecialGameObject*>& SpecialObjects() = 0;
};