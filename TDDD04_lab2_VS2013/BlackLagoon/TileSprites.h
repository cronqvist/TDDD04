#pragma once

#include "hge.h"
#include "hgeSprite.h"
#include "ITileSprites.h"

class TileSprites : public ITileSprites
{
public:
	TileSprites(HTEXTURE tileTextureAtlas, 
		float tileWidth, float tileHeight,
		float borderOffset, float tileSpace);
	~TileSprites();

	hgeSprite* GetFull1();
	hgeSprite* GetFull2();
	hgeSprite* GetFull3();
	hgeSprite* GetHalf1();
	hgeSprite* GetHalf2();
	hgeSprite* GetIsland();
	hgeSprite* GetThreeQuarters();
	hgeSprite* GetOneQuarter();
	hgeSprite* GetBlank();

	float GetTileWidth();
	float GetTileHeight();

private:
	hgeSprite** m_terrainTileSprites;
	size_t m_nrOfTerrainTileSprites;
	float m_tileWidth;
	float m_tileHeight;
};
