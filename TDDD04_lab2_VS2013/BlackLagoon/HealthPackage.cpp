#include "HealthPackage.h"

HealthPackage::HealthPackage(int amount, hgeSprite* sprite, int type) 
	: m_amount(amount),  SpecialGameObject(sprite, type)
{
}

HealthPackage::~HealthPackage()
{
}

void HealthPackage::action(GameObject* go)
{
	go->Health += m_amount;
}