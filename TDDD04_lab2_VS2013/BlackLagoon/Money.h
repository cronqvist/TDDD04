#pragma once
#include "specialgameobject.h"

class Money :
	public SpecialGameObject
{
public:
	Money(int amount, hgeSprite* sprite = 0, int type = -1);
	~Money();
	void action(GameObject* go);
private:
	int m_amount;
};
