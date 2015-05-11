#include "GunTurretAI.h"

#include "GameObject.h"
#include "IGameObjectManager.h"

GunTurretAI::GunTurretAI() :
	m_fireTimer(0),
	m_waitTime(4),
	m_angleToTarget(M_PI)
{
}

GunTurretAI::~GunTurretAI()
{
}

void GunTurretAI::tick(GameObject* go, float deltaTime, IGameObjectManager* gom)
{
	Player* player = gom->getPlayer();

	Coord offset = player->getPosition() - go->getPosition();
	hgeVector v(offset.x, offset.y);

	float angle = NormalizeAngle( v.Angle());
	angle -= go->getRotation();

	// Store for fire to use
	m_angleToTarget =  angle;

	go->setAngularVelocity( (m_angleToTarget / M_PI_2) * GUN_TURRET_ANGULAR_ACCELERATION );
}

bool GunTurretAI::fire(float deltaTime)
{
	if ( (m_fireTimer > m_waitTime) && (fabs(m_angleToTarget) < (M_PI_2 / 2.0f)) )
	{
		m_fireTimer = 0;
		if (m_waitTime == 4.0f) {
			m_waitTime = 0.4f;
		} else {
			m_waitTime = 4.0f;
		}
		return true;
	} else {
		m_fireTimer += deltaTime;		
	}
	return false;
}