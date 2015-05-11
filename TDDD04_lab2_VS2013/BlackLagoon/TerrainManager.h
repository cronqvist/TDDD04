#ifndef TERRAIN_MANAGER_H
#define TERRAIN_MANAGER_H

#include "stdafx.h"
#include "ITerrainManager.h"
#include "ITerrainTileTypes.h"
#include "BasicGameObject.h"
#include "IPhysicsComponent.h"

class TerrainManager : public ITerrainManager
{
public:
	TerrainManager(ITerrainTileTypes* terrainTileTypes);
	virtual ~TerrainManager();

	CoordType getPixelWidth();
	CoordType getPixelHeight();
	void loadTerrain(int* terrainLayout, int width, int height);
	void render(Rect cameraView);
	bool checkCollision(IPhysicsComponent* physComp, BasicGameObject* bgo, Rect area);

private:
	TerrainTile* getTile(int x_index, int y_index);
	int getInternalIndex(int x_index, int y_index);
	int getXTileIndexFromCoordinate(const Coord& coord);
	int getYTileIndexFromCoordinate(const Coord& coord);

private:
	int* m_terrainLayout;
	int m_width;
	int m_height;
	
	ITerrainTileTypes& m_terrainTileTypes;
};

#endif