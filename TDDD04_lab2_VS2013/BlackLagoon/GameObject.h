#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class IGameObjectManager;
class IAI;

#include "stdafx.h"
#include "BasicGameObject.h"

#include "IAI.h"
#include "Shot.h"

//#include "IGameObjectManager.h"
class IGameObjectManager;

class GameObject :
	public BasicGameObject
{
public:
	GameObject(hgeSprite* sprite = 0, IAI* AI = 0);
	virtual ~GameObject();

public:
	void setStats(int health, int money, int ammo);
	
	virtual bool fire(float deltaTime);
	virtual void tick(float deltaTime, IGameObjectManager* gom);
	virtual bool isDead();

	virtual void setNewShot(Shot* shot);

	IAI* getAI();
	void setAI(IAI* AI);

	
public:
	int			Money;
	int			Health;
	int			Ammo;

protected:
	IAI*		m_AI;

};

#endif