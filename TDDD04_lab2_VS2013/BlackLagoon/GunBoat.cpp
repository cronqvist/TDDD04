#include "GunBoat.h"
#include "IGameObjectManager.h"
#include "IPhysicsComponent.h"

GunBoat::GunBoat(hgeSprite* sprite, IAI* AI) :
	GameObject(sprite, AI),
		m_turret(0)
{
}

GunBoat::~GunBoat()
{
}

void GunBoat::destroy()
{
	SAFE_DESTROY(m_turret);
}

void GunBoat::tick(float deltaTime, IGameObjectManager* gom)
{
	GameObject::tick(deltaTime, gom);
	if (m_turret)
		m_turret->tick(deltaTime, gom);
}

void GunBoat::setTurret(GunTurret* turret)
{
	m_turret = turret;
	m_turret->setActive(this->getActive());
	m_turret->setVelocity(hgeVector(0,0));
	m_turret->setAngularVelocity(0);
	setTurretPosition();
}

void GunBoat::setNewShot(Shot* shot)
{
	m_turret->setNewShot(shot);
}

bool GunBoat::fire(float deltaTime)
{
	if (m_turret)
		return m_turret->fire(deltaTime);
	else
		return this->getAI()->fire(deltaTime);
}

void GunBoat::render(Rect& cameraView)
{
	BasicGameObject::render(cameraView);
	if (m_turret)
		m_turret->render(cameraView);
}

void GunBoat::setPosition(Coord& position)
{
	BasicGameObject::setPosition(position);
	setTurretPosition();
}

void GunBoat::setActive(bool active)
{
	BasicGameObject::setActive(active);
	if (m_turret)
		m_turret->setActive(active);
}

void GunBoat::setRotation(float rotation)
{
	BasicGameObject::setRotation(rotation);
	
	float difRot = NormalizeAnglePI(m_turret->getRotation()- m_rotation);

	if (fabs(difRot) > (0.75f * M_PI))
	{
		if (difRot > 0)
			difRot = 0.75f * M_PI;
		else
			difRot = -0.75f * M_PI;

		m_turret->setRotation(m_rotation + difRot);
	}


}

void GunBoat::setTurretPosition()
{
	//FIXME:
	if (m_turret)
	{
		hgeVector v = CreateVectorFromAngle(m_rotation, 30);
		Coord pos(m_position);
		
		pos.offset(v.x, v.y);

		m_turret->setPosition(pos);
	}
}

void GunBoat::move(IPhysicsComponent* physComp, float deltaTime)
{
	if (m_turret)
		m_turret->move(physComp, deltaTime);

	physComp->moveObject(this, deltaTime);
}