#include "GunBoatAI.h"

#include "GameObject.h"
#include "IGameObjectManager.h"

GunBoatAI::GunBoatAI()
{
}

GunBoatAI::~GunBoatAI()
{
}

void GunBoatAI::tick(GameObject* go, float deltaTime, IGameObjectManager* gom)
{
	go->setVelocity(hgeVector(0, 10));
}
bool GunBoatAI::fire(float deltaTime)
{
	return false;
}