#ifndef PLAYERAI_H
#define PLAYERAI_H

#include "stdafx.h"
#include "IAI.h"
#include "IInputDevice.h"

class PlayerAI :
	public IAI
{
public:
	PlayerAI(IInputDevice* input);
	~PlayerAI();

public:
	virtual void tick(GameObject* go, float deltaTime, IGameObjectManager* gom);
	virtual bool fire(float deltaTime);

private:
	IInputDevice* m_input;
};

#endif