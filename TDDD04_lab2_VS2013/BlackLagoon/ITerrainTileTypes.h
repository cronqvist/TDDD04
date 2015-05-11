#pragma once

#include "terraintile.h"

class ITerrainTileTypes
{
public:
	virtual ~ITerrainTileTypes(){};
	virtual TerrainTile*& operator[](const int i) = 0;
	virtual float GetTileWidth() = 0;
	virtual float GetTileHeight() = 0;
};
