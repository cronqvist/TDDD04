#ifndef GUN_TURRET_AI_H
#define GUN_TURRET_AI_H

#include "IAI.h"

class GunTurretAI :
	public IAI
{
public:
	GunTurretAI();
	~GunTurretAI();

public:
	virtual void tick(GameObject* go, float deltaTime, IGameObjectManager* gom);
	virtual bool fire(float deltaTime);

private:
	float m_fireTimer;
	float m_waitTime;

	float m_angleToTarget;
};

#endif