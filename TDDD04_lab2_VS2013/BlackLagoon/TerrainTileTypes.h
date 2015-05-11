#pragma once

#include "ITerraintileTypes.h"
#include "ITileSprites.h"

class TerrainTileTypes : public ITerrainTileTypes
{
public:
	TerrainTileTypes(ITileSprites* tileSprites)
	{
		m_tileWidth = tileSprites->GetTileWidth();
		m_tileHeight = tileSprites->GetTileHeight();

		Rect empty(0,0,0,0);
		Rect full(0,0,m_tileWidth, m_tileHeight);
		Rect topHalf(0,0,m_tileWidth,m_tileHeight/2.0f);
		Rect leftHalf(0,0,m_tileWidth/2.0f,m_tileHeight);
		Rect rightHalf(m_tileWidth/2.0f,0,m_tileWidth,m_tileHeight);
		Rect bottomHalf(0,m_tileHeight/2.0f,m_tileWidth,m_tileHeight);

		Rect bottomRightCorner(m_tileWidth/2.0f,m_tileHeight/2.0f,m_tileWidth,m_tileHeight);
		Rect bottomLeftCorner(0,m_tileHeight/2.0f,m_tileWidth/2.0f,m_tileHeight);
		Rect topRightCorner(m_tileWidth/2.0f,0,m_tileWidth,m_tileHeight/2.0f);
		Rect topLeftCorner(0,0,m_tileWidth/2.0f,m_tileHeight/2.0f);

		Rect island(9,2,m_tileWidth-7,m_tileHeight-2);

		// Create terrainTiles and store in array
		m_tileTypes[0] = new TerrainTile(tileSprites->GetFull1(),full);

		m_tileTypes[1] = new TerrainTile(tileSprites->GetThreeQuarters(), full);
		m_tileTypes[2] = new TerrainTile(tileSprites->GetHalf1(), topHalf, M_PI_2);
		m_tileTypes[3] = new TerrainTile(tileSprites->GetThreeQuarters(), full, M_PI_2);
		m_tileTypes[4] = new TerrainTile(tileSprites->GetHalf1(), leftHalf);
		
		m_tileTypes[5] = new TerrainTile(tileSprites->GetBlank(), empty);
		
		m_tileTypes[6] = new TerrainTile(tileSprites->GetHalf1(), rightHalf, M_PI);
		m_tileTypes[7] = new TerrainTile(tileSprites->GetThreeQuarters(), full, -M_PI_2);
		m_tileTypes[8] = new TerrainTile(tileSprites->GetHalf1(), bottomHalf, -M_PI_2);
		m_tileTypes[9] = new TerrainTile(tileSprites->GetThreeQuarters(), full, M_PI);

		m_tileTypes[10] = new TerrainTile(tileSprites->GetFull2(), full);

		m_tileTypes[11] = new TerrainTile(tileSprites->GetOneQuarter(), bottomRightCorner, M_PI);
		m_tileTypes[12] = new TerrainTile(tileSprites->GetOneQuarter(), bottomLeftCorner, -M_PI_2);
		m_tileTypes[13] = new TerrainTile(tileSprites->GetOneQuarter(), topRightCorner, M_PI_2);
		m_tileTypes[14] = new TerrainTile(tileSprites->GetOneQuarter(), topLeftCorner);

		m_tileTypes[15] = new TerrainTile(tileSprites->GetIsland(), island);

		m_tileTypes[16] = new TerrainTile(tileSprites->GetHalf2(), leftHalf);
		m_tileTypes[17] = new TerrainTile(tileSprites->GetHalf2(), rightHalf, M_PI);
		m_tileTypes[18] = new TerrainTile(tileSprites->GetHalf2(), topHalf, M_PI_2);
		m_tileTypes[19] = new TerrainTile(tileSprites->GetHalf2(), bottomHalf, -M_PI_2);

		m_tileTypes[20] = new TerrainTile(tileSprites->GetFull3(), full);
	}

	~TerrainTileTypes()
	{
		for(size_t i = 0; i < 21; i++) {
			delete m_tileTypes[i];
		}	
	}

	TerrainTile*& operator[](const int i)
	{
		return m_tileTypes[i];
	}

	float GetTileWidth()
	{ 
		return m_tileWidth; 
	}
	float GetTileHeight()
	{ 
		return m_tileHeight; 
	}

private:
	TerrainTile* m_tileTypes[21];
	float m_tileWidth;
	float m_tileHeight;

};
