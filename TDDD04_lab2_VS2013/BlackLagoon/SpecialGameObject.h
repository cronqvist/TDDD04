#pragma once
#include "basicgameobject.h"
#include "gameobject.h"

class GameObject;

class SpecialGameObject :
	public BasicGameObject
{
public:
	SpecialGameObject(hgeSprite* sprite = 0, int type = -1) : BasicGameObject(sprite, type){};
	virtual ~SpecialGameObject(){};

	virtual void action(GameObject* go)=0;
};
