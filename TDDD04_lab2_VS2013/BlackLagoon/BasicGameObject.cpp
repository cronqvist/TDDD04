#include "BasicGameObject.h"
#include "PhysicsComponent.h"

BasicGameObject::BasicGameObject(hgeSprite* sprite, int type) :
	m_position(Coord(0.0f, 0.0f)),
	m_rotation(0.0f),
	m_sprite(sprite),
	m_velocity(hgeVector(0,0)),
	m_angularVelocity(0.0f),
	m_active(false),
	m_type(type)
{
}

BasicGameObject::~BasicGameObject()
{
	// Game Object Factory handles the sprites.
	// Do not delete the sprite!
	m_sprite = 0;
}

void BasicGameObject::destroy()
{
	delete this;
}

void BasicGameObject::render(Rect& cameraView)
{
	Coord relPos = m_position - cameraView.topLeft();
	m_sprite->RenderEx(relPos.x, relPos.y, m_rotation, 1.0f, 1.0f);
}

hgeSprite* BasicGameObject::getSprite()
{

	return m_sprite;
}

void BasicGameObject::setPosition(Coord& position)
{
	m_position = position;
}
Coord BasicGameObject::getPosition()
{
	return m_position;
}

void BasicGameObject::offsetPosition(Coord& offset)
{
	m_position.offset(offset);
}

void BasicGameObject::setRotation(float rotation)
{
	m_rotation = NormalizeAngle(rotation);
}

float BasicGameObject::getRotation()
{
	return m_rotation;
}

void BasicGameObject::setActive(bool active)
{
	m_active = active;
}

bool BasicGameObject::getActive()
{
	return m_active;
}

void BasicGameObject::setVelocity(const hgeVector& velocity)
{
	m_velocity = velocity;
}
hgeVector BasicGameObject::getVelocity()
{
	return m_velocity;
}

void BasicGameObject::setAngularVelocity(float angularVelocity)
{
	m_angularVelocity = angularVelocity;
}

float BasicGameObject::getAngularVelocity()
{
	return m_angularVelocity;
}

void BasicGameObject::getBoundingBox(hgeRect* rect)
{
	m_sprite->GetBoundingBoxEx(m_position.x, m_position.y, m_rotation, 1.0f, 1.0f, rect);
}

Rect BasicGameObject::getRectangle()
{
	hgeRect spriteRect;
	getBoundingBox(&spriteRect);
	return ConvertBoundingBoxToRect(&spriteRect);
}

void BasicGameObject::move(IPhysicsComponent* physComp, float deltaTime)
{
	physComp->moveObject(this, deltaTime);
}

bool BasicGameObject::collide(IPhysicsComponent* physComp, Rect& rect)
{
	return physComp->checkObjectCollision(this, rect);
}

int BasicGameObject::getType()
{
	return m_type;
}