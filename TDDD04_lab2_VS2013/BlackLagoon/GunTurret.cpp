#include "GunTurret.h"

GunTurret::GunTurret(hgeSprite* sprite, IAI* AI) :
	GameObject(sprite, AI)
{
}

GunTurret::~GunTurret()
{
}

void GunTurret::setNewShot(Shot* shot)
{
	hgeVector v = CreateVectorFromAngle(this->getRotation(),
		(this->getSprite()->GetWidth() + shot->getSprite()->GetHeight()) / 2.0f);
	Coord pos = this->getPosition();
	pos.offset(v.x, v.y);
	shot->setPosition(pos);
	shot->setVelocity(CreateVectorFromAngle(this->getRotation(), 1));
	shot->setSpeed(ENEMY_SHOT_TOP_SPEED);
	shot->setRotation(this->getRotation());
}