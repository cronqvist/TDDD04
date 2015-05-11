#pragma once
#include "specialgameobject.h"

class Ammo :
	public SpecialGameObject
{
public:
	Ammo(int amount, hgeSprite* sprite = 0, int type = -1);
	~Ammo();
	void action(GameObject* go);

private:
	int m_amount;
};
