#pragma once

#include "stdafx.h"
#include "BasicGameObject.h"
#include "IPhysicsComponent.h"
#include "TerrainTile.h"

class ITerrainManager
{
public:
	virtual ~ITerrainManager(){};

	virtual CoordType getPixelWidth() = 0;
	virtual CoordType getPixelHeight() = 0;
	virtual void loadTerrain(int* terrainLayout, int width, int height) = 0;
	virtual void render(Rect cameraView) = 0;
	virtual bool checkCollision(IPhysicsComponent* physComp, BasicGameObject* bgo, Rect area) = 0;
};