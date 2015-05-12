#include "Player.h"

Player::Player(hgeSprite* sprite, IAI* AI) :
	GameObject(sprite, AI)
{
}

Player::~Player()
{
}

void Player::setNewShot(Shot* shot)
{
	static bool left = true;
	left = !left;

	hgeVector v = CreateVectorFromAngle(this->getRotation(), 19+shot->getSprite()->GetHeight());
	if (left)
		v += CreateVectorFromAngle(this->getRotation()+M_PI_2, 3);
	else
		v -= CreateVectorFromAngle(this->getRotation()+M_PI_2, 3);

	Coord pos = this->getPosition();
	pos.offset(v.x, v.y);
	shot->setPosition(pos);
	shot->setVelocity(CreateVectorFromAngle(this->getRotation(), 1));
	shot->setSpeed(PLAYER_SHOT_TOP_SPEED);
	shot->setRotation(this->getRotation());
	Ammo--;
}

bool Player::fire(float deltaTime)
{
	if (m_AI->fire(deltaTime))
	{
		if (Ammo > 0) {
			return true;
		}
	}
	return false;
}

void Player::setVelocity(const hgeVector& velocity)
{
	BasicGameObject::setVelocity(velocity);
	m_velocity.Clamp(PLAYER_TOP_SPEED);
}