#ifndef GUN_BOAT_H
#define GUN_BOAT_H

#include "GameObject.h"
#include "GunTurret.h"

class IGameObjectManager;
class IPhysicsComponent;

class GunBoat :
	public GameObject
{
public:
	GunBoat(hgeSprite* sprite = 0, IAI* AI = 0);
	~GunBoat();

public:
	virtual void render(Rect& cameraView);
	virtual bool fire(float deltaTime);
	virtual void tick(float deltaTime, IGameObjectManager* gom);
	virtual void destroy();

	virtual void setPosition(Coord& position);
	virtual void setRotation(float rotation);
	virtual void setActive(bool active);

	void setTurret(GunTurret* turret);

	virtual void setNewShot(Shot* shot);

	virtual void move(IPhysicsComponent* physComp, float deltaTime);

private:
	void setTurretPosition();

private:
	GunTurret* m_turret;

};

#endif