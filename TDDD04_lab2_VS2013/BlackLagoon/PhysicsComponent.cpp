#include "PhysicsComponent.h"

using std::vector;

PhysicsComponent::PhysicsComponent()
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::move(IGameObjectManager* gom, float deltaTime)
{
	// Player
	moveObject(gom->getPlayer(), deltaTime);

	// Enemies
	for (vector<GameObject*>::iterator it = gom->Enemies().begin(); it != gom->Enemies().end(); it++)
	{
		(*it)->move(this, deltaTime);
	}
	
	// Special objects
	for (vector<SpecialGameObject*>::iterator it = gom->SpecialObjects().begin(); it != gom->SpecialObjects().end(); it++)
	{
		(*it)->move(this, deltaTime);
	}

	// Player shots
	for (int i = 0; i < gom->getPlayerShotsInUse(); i ++)
	{
		gom->getPlayerShot(i)->move(this, deltaTime);
	}

	// Enemy shots
	for (int i = 0; i < gom->getEnemyShotsInUse(); i ++)
	{
		gom->getEnemyShot(i)->move(this, deltaTime);
	}
}

void PhysicsComponent::moveObject(BasicGameObject* bgo, float deltaTime)
{
	bgo->setPosition(Coord(bgo->getPosition().x + bgo->getVelocity().x * deltaTime,
		bgo->getPosition().y + bgo->getVelocity().y * deltaTime));
	bgo->setRotation(bgo->getRotation() + bgo->getAngularVelocity() * deltaTime);
}

bool PhysicsComponent::checkObjectCollision(BasicGameObject* bgo, Rect& rect)
{
	return (bgo->getRectangle().overlap(rect));
}