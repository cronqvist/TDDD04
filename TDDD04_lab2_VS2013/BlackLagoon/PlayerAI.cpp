#include "PlayerAI.h"

#include "GameObject.h"
#include "IGameObjectManager.h"

PlayerAI::PlayerAI(IInputDevice* input) :
	m_input(input)
{
}

PlayerAI::~PlayerAI()
{
}

bool PlayerAI::fire(float deltaTime)
{
	return (m_input->fire());
}

void PlayerAI::tick(GameObject* go, float deltaTime, IGameObjectManager* gom)
{
	go->setVelocity(hgeVector(0,0));
	go->setAngularVelocity(0.0f);

	if(m_input->down())
	{
		go->setVelocity(go->getVelocity() + hgeVector(0, PLAYER_ACCELERATION));
	}
	if(m_input->up())
	{
		go->setVelocity(go->getVelocity() + hgeVector(0, -PLAYER_ACCELERATION));
	}
	if(m_input->left())
	{
		go->setVelocity(go->getVelocity() + hgeVector(-PLAYER_ACCELERATION,0));
	}
	if(m_input->right())
	{
		go->setVelocity(go->getVelocity() + hgeVector(PLAYER_ACCELERATION,0));
	}

	if(m_input->down2())
	{
		go->setVelocity(go->getVelocity() + CreateVectorFromAngle(go->getRotation() + M_PI, PLAYER_ACCELERATION));
	}
	if(m_input->up2())
	{
		go->setVelocity(go->getVelocity() + CreateVectorFromAngle(go->getRotation(), PLAYER_ACCELERATION));
	}
	if(m_input->left2())
	{
		go->setVelocity(go->getVelocity() + CreateVectorFromAngle(go->getRotation() - (M_PI/2.0f), PLAYER_ACCELERATION));
	}
	if(m_input->right2())
	{
		go->setVelocity(go->getVelocity() + CreateVectorFromAngle(go->getRotation() + (M_PI/2.0f), PLAYER_ACCELERATION));
	}
	if(m_input->turnLeft())
	{
		go->setAngularVelocity(go->getAngularVelocity() - PLAYER_ANGULAR_ACCELERATION);
	}
	if(m_input->turnRight())
	{
		go->setAngularVelocity(go->getAngularVelocity() + PLAYER_ANGULAR_ACCELERATION);
	}
}