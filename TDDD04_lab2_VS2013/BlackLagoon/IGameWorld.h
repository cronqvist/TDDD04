#pragma once

#include "ILevelManager.h"

class IGameWorld
{
public:
	virtual ~IGameWorld(){};
	virtual void tick(float deltaTime) = 0;
	virtual void reset() = 0;
	virtual void loadLevel(ILevelManager* levelManager) = 0;
	virtual void render() = 0;
	virtual int getScore() = 0;
	virtual void setGamePaused(bool pause) = 0;
	virtual bool getGamePaused() = 0;
	virtual void toggleGamePaused() = 0;
	virtual float getGameTime() = 0;
};