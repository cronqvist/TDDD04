#pragma once

#include "IGameObjectManager.h"
#include "ITerrainManager.h"
#include <fstream>

class ILevelManager
{
public:
	virtual ~ILevelManager(){};

	virtual void reset()=0;
	virtual void setLevel(int level)=0;
	virtual int getLevel()=0;
	virtual int levelUp()=0;
	virtual bool lastLevel()=0;
	virtual void render(float x, float y)=0;
	virtual void loadLevel(IGameObjectManager *GOM, ITerrainManager *TM, char const* filename=0)=0;
	virtual void loadLevel(IGameObjectManager *GOM, ITerrainManager *TM, std::ifstream &f)=0;
};