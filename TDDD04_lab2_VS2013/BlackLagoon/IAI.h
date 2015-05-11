#ifndef IAI_H
#define IAI_H

#include "stdafx.h"

class GameObject;
class IGameObjectManager;

class IAI
{
public:
	IAI(int level = 1);
public:
	virtual ~IAI();

public:
	void virtual tick(GameObject* go, float deltaTime, IGameObjectManager* gom) = 0;
	virtual bool fire(float deltaTime) = 0;

public:
	void setLevel(int level);
	
protected:
	int m_level;

};

#endif