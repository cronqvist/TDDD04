#include "TileSprites.h"

TileSprites::TileSprites(HTEXTURE tileTextureAtlas, 
						 float tileWidth, 
						 float tileHeight, 	
						 float borderOffset, 
						 float tileSpace)
: m_tileWidth(tileWidth), m_tileHeight(tileHeight)
{
	size_t xNrOfSprites = 3;
	size_t yNrOfSprites = 3;


	m_nrOfTerrainTileSprites = xNrOfSprites * yNrOfSprites;
	m_terrainTileSprites = new hgeSprite *[m_nrOfTerrainTileSprites];

	size_t index;
	hgeSprite* newSprite;

	float xCoord;
	float yCoord;
	float hotSpotXOffset = tileWidth/2.0f;
	float hotSpotYOffset = tileHeight/2.0f;

	for (size_t y = 0; y < yNrOfSprites; y++)
	{
		for (size_t x = 0; x < xNrOfSprites; x++)
		{
			xCoord = borderOffset + (x * (tileWidth + tileSpace));
			yCoord = borderOffset + (y * (tileHeight + tileSpace));
			
			newSprite = new hgeSprite(tileTextureAtlas, xCoord, yCoord, tileWidth, tileHeight);
			newSprite->SetHotSpot(hotSpotXOffset, hotSpotYOffset);
			newSprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);

			index = (y*xNrOfSprites) + x;
			m_terrainTileSprites[index] = newSprite;
		}
	}
}

TileSprites::~TileSprites()
{
	for(size_t i = 0; i < m_nrOfTerrainTileSprites; i++)
	{
		delete m_terrainTileSprites[i];
	}
	delete[] m_terrainTileSprites;
}

float TileSprites::GetTileWidth()
{
	return m_tileWidth;
}

float TileSprites::GetTileHeight()
{
	return m_tileHeight;
}

hgeSprite* TileSprites::GetFull1()
{
	return m_terrainTileSprites[0];
}

hgeSprite* TileSprites::GetFull2()
{
	return m_terrainTileSprites[1];
}

hgeSprite* TileSprites::GetFull3()
{
	return m_terrainTileSprites[2];
}

hgeSprite* TileSprites::GetHalf1()
{
	return m_terrainTileSprites[3];
}

hgeSprite* TileSprites::GetHalf2()
{
	return m_terrainTileSprites[4];
}

hgeSprite* TileSprites::GetIsland()
{
	return m_terrainTileSprites[5];
}

hgeSprite* TileSprites::GetThreeQuarters()
{
	return m_terrainTileSprites[6];
}

hgeSprite* TileSprites::GetOneQuarter()
{
	return m_terrainTileSprites[7];
}

hgeSprite* TileSprites::GetBlank()
{
	return m_terrainTileSprites[8];
}