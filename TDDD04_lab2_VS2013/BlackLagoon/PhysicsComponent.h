#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "stdafx.h"
#include "IPhysicsComponent.h"
#include "GameObject.h"
#include "IGameObjectManager.h"

class PhysicsComponent : public IPhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();

public:
	virtual void move(IGameObjectManager* gom, float deltaTime);
	virtual void moveObject(BasicGameObject* bgo, float deltaTime);
	virtual bool checkObjectCollision(BasicGameObject* bgo1, Rect& rect);

private:
	

};

#endif