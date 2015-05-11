#pragma once

#include "IGameObjectManager.h"

class IPhysicsComponent
{
public:
	virtual ~IPhysicsComponent(){};

	virtual void move(IGameObjectManager *gom, float deltaTime) = 0;
	virtual void moveObject(BasicGameObject *bgo, float deltaTime) = 0;
	virtual bool checkObjectCollision(BasicGameObject *bgo1, Rect& rect) = 0;

};