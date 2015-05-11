#include "Shot.h"

Shot::Shot(hgeSprite* sprite, float speed, int damage) :
	BasicGameObject(sprite),
	m_speed(speed),
	Damage(damage)
{
	m_velocity.Clamp(m_speed);
}

Shot::~Shot()
{
}

void Shot::setSpeed(float speed)
{
	m_speed = speed;
	m_velocity *= (m_speed / this->getVelocity().Length()) ;
}