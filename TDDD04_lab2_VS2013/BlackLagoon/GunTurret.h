#ifndef GAME_TURRET_H
#define GAME_TURRET_H

#include "GameObject.h"

class GunTurret :
	public GameObject
{
public:
	GunTurret(hgeSprite* sprite = 0, IAI* AI = 0);
	~GunTurret();

	virtual void setNewShot(Shot* shot);
};

#endif