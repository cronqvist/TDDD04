#pragma once
#include "player.h"
#include "gameobject.h"
#include "shot.h"
#include "basicgameobject.h"
#include "specialgameobject.h"
#include "IInputDevice.h"

#include "GameObjectTypeDefinitions.h"

class IGameObjectFactory
{
public:
	virtual ~IGameObjectFactory(){};

	virtual Player* getPlayer(IInputDevice *input) = 0;
	virtual GameObject* getEnemy(int type) = 0;
	virtual SpecialGameObject* getSpecialObject(int type) = 0;
	virtual Shot* getPlayerShot() = 0;
	virtual Shot* getEnemyShot() = 0;
	virtual void release(SpecialGameObject *&bgo) = 0;
	virtual void release(GameObject *&go) = 0;
	virtual void release(Player *&player) = 0;
	virtual void release(Shot *&shot) = 0;

};