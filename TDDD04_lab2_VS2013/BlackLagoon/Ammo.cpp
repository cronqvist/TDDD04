#include "Ammo.h"

Ammo::Ammo(int amount, hgeSprite* sprite, int type)
	: m_amount(amount), SpecialGameObject(sprite, type)
{
}

Ammo::~Ammo()
{
}

void Ammo::action(GameObject* go)
{
	go->Ammo += m_amount;
}