#ifndef SHOT_H
#define SHOT_H

#include "basicgameobject.h"

class Shot :
	public BasicGameObject
{
public:
	Shot(hgeSprite* sprite = 0, float speed = SHOT_TOP_SPEED, int damage = SHOT_DAMAGE);
	~Shot();

public:
	void setSpeed(float speed = SHOT_TOP_SPEED);
	int Damage;
private:
	float m_speed;
	
};

#endif