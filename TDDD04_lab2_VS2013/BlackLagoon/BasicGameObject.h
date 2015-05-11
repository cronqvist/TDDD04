#ifndef BASIC_GAME_OBJECT_H
#define BASIC_GAME_OBJECT_H

#include "stdafx.h"

class IPhysicsComponent;

class BasicGameObject
{
public:
	BasicGameObject(hgeSprite* sprite = 0, int type = -1);

	virtual ~BasicGameObject();

public:
	virtual void render(Rect& cameraView);

	virtual void destroy();
	virtual hgeSprite* getSprite();

	virtual void setPosition(Coord& position);
	virtual Coord getPosition();

	virtual void setRotation(float rotation);
	virtual float getRotation();
	virtual void offsetPosition(Coord& position);

	virtual void setActive(bool active);
	virtual bool getActive();

	virtual void setVelocity(const hgeVector& velocity);
	virtual hgeVector getVelocity();

	virtual void setAngularVelocity(float angularVelocity);
	virtual float getAngularVelocity();

	virtual void getBoundingBox(hgeRect* rect);
	virtual Rect getRectangle();

	virtual void move(IPhysicsComponent* physComp, float deltaTime);
	virtual bool collide(IPhysicsComponent* physComp, Rect& rect);

	virtual int getType();

protected:
	hgeSprite* m_sprite;

	hgeVector	m_velocity;
	float		m_angularVelocity;

	Coord		m_position;
	float		m_rotation;
	bool		m_active;

	int			m_type;
};

#endif