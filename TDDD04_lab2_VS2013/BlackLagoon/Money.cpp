#include "Money.h"

Money::Money(int amount, hgeSprite* sprite, int type) 
	: m_amount(amount), SpecialGameObject(sprite, type)
{
}

Money::~Money()
{
}

void Money::action(GameObject* go)
{
	go->Money += m_amount;
}