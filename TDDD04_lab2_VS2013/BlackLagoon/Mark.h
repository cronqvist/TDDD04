#pragma once
#include "specialgameobject.h"

class Mark :
	public SpecialGameObject
{
public:
	Mark(hgeSprite* sprite = 0, int type = -1);
	~Mark();
	void action(GameObject* go);
};
