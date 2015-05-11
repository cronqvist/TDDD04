#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

#include "stdafx.h"

#include "IAI.h"

class Shot;

class Player :
	public GameObject
{
public:
	Player(hgeSprite* sprite = 0, IAI* AI = 0);
	virtual ~Player();

	//Inherited from GameObject
	void setNewShot(Shot* shot);
	bool fire(float deltaTime);
	//Inherited from GameObject::BasicGameObject
	virtual void setVelocity(const hgeVector& velocity);
};

#endif