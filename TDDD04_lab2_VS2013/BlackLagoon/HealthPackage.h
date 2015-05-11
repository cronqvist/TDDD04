#pragma once
#include "specialgameobject.h"
#include "gameobject.h"

class GameObject;

class HealthPackage :
	public SpecialGameObject
{
public:
	HealthPackage(int amount, hgeSprite* sprite = 0, int type = -1);
	~HealthPackage();
	void action(GameObject* go);

private:
	int m_amount;
};
