#ifndef GUN_BOAT_AI
#define GUN_BOAT_AI

#include "IAI.h"

class GunBoatAI :
	public IAI
{
public:
	GunBoatAI();
	~GunBoatAI();

public:
	virtual void tick(GameObject* go, float deltaTime, IGameObjectManager* gom);
	virtual bool fire(float deltaTime);
};

#endif