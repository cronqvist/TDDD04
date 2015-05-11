#include "GameObject.h"
#include "IGameObjectManager.h"

GameObject::GameObject(hgeSprite* sprite, IAI* AI) :
	BasicGameObject(sprite),
	m_AI(AI),	
	Money(0),
	Health(0),
	Ammo(0)
{
}

GameObject::~GameObject()
{
	SAFE_DELETE(m_AI);
}

void GameObject::setStats(int health, int money, int ammo)
{
	this->Health = health;
	this->Money = money;
	this->Ammo = ammo;
}

bool GameObject::fire(float deltaTime)
{
	if (m_AI)
		return m_AI->fire(deltaTime);

	return false;
}

void GameObject::tick(float deltaTime, IGameObjectManager* gom)
{
	if (m_AI)
		m_AI->tick(this, deltaTime, gom);
}

bool GameObject::isDead()
{
	return (this->Health < 0);
}

void GameObject::setNewShot(Shot* shot)
{
	shot->setVelocity(this->getVelocity());
	shot->setRotation(this->getRotation());
}

void GameObject::setAI(IAI* AI)
{
	m_AI = AI;
}

IAI* GameObject::getAI()
{
	return m_AI;
}