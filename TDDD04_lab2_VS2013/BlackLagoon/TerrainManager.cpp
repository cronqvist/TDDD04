#include "TerrainManager.h"

TerrainManager::TerrainManager(ITerrainTileTypes* terrainTileTypes) 
		:
			m_terrainLayout(0),
			m_width(0), m_height(0),
			m_terrainTileTypes(*terrainTileTypes)
{
}

TerrainManager::~TerrainManager()
{
	delete[] m_terrainLayout;
}

float TerrainManager::getPixelWidth()
{
	return (m_terrainTileTypes.GetTileWidth() * static_cast<float>(m_width));
}

float TerrainManager::getPixelHeight()
{
	return (m_terrainTileTypes.GetTileHeight() * static_cast<float>(m_height));
}

void TerrainManager::loadTerrain(int* terrainLayout, int width, int height)
{
	
	m_width = width;
	m_height = height;

	// Temp value
	int nrOfTiles = width*height;

	if ( (nrOfTiles > 0) && (terrainLayout != 0) )
	{

		// Create array to store the tile layout of the world terrain.
		m_terrainLayout = new int[nrOfTiles];

		// TODO: memcpy(void * destination, void * source, size_t bytes); in string.h instead
		// memcpy(m_terrainTiles, terrainLayout, sizeof(int)*nrOfTiles);
		if (terrainLayout != 0)
		{
			for (int i = 0; i < nrOfTiles; i++)
			{
				m_terrainLayout[i] = terrainLayout[i];
			}
		}
	}
}

void TerrainManager::render(Rect cameraView)
{
	TerrainTile* tile;

	int startX = max(0, getXTileIndexFromCoordinate(cameraView.topLeft()));
	int startY = max(0, getYTileIndexFromCoordinate(cameraView.topLeft()));
	int stopX = max(0, getXTileIndexFromCoordinate(cameraView.bottomRight()));
	int stopY = max(0, getYTileIndexFromCoordinate(cameraView.bottomRight()));

	stopX = min(stopX, (m_width -1));
	stopY = min(stopY, (m_height - 1));
	startX = min(startX, stopX);
	startY = min(startY, stopY);

	float tileWidth = m_terrainTileTypes.GetTileWidth();
	float tileHeight = m_terrainTileTypes.GetTileHeight();

	// Render coordinates. Will be updated for every tile rendered.
	// The first will most likely start at negative values.
	
	float y = (startY * tileHeight) - cameraView.topLeft().y;
	for (int y_index = startY; y_index <= stopY; y_index++) {
		float x = (startX * tileWidth) - cameraView.topLeft().x;
		for (int x_index = startX; x_index <= stopX; x_index++) {
			tile = getTile(x_index, y_index);
			if (tile != 0)
			{
				tile->render(x, y);
				x += tileWidth;
			}
		}
		y += tileHeight;
	}
}

TerrainTile* TerrainManager::getTile(int x_index, int y_index)
{
	if ( (0 <= x_index) && (x_index < m_width) && (0 <= y_index) && (y_index < m_height))
	{
		int terrainTileType = m_terrainLayout[getInternalIndex(x_index, y_index)];
		return m_terrainTileTypes[terrainTileType];
	} else{
		return 0;
	}
}

int TerrainManager::getInternalIndex(int x_index, int y_index)
{
	return (y_index * m_width) + x_index;
}


int TerrainManager::getXTileIndexFromCoordinate(const Coord& coord)
{
	return static_cast<int>( floor(coord.x / m_terrainTileTypes.GetTileWidth()));
}


int TerrainManager::getYTileIndexFromCoordinate(const Coord& coord)
{
	return static_cast<int>( floor(coord.y / m_terrainTileTypes.GetTileWidth()));
}


bool TerrainManager::checkCollision(IPhysicsComponent* physComp, BasicGameObject* bgo, Rect area)
{
	TerrainTile*	tile;
	hgeRect			boundedBox;
	Rect			rect;

	area.bottomRight().x = this->getPixelWidth();
	area.bottomRight().y = this->getPixelHeight();

	int startX = max(0, getXTileIndexFromCoordinate(area.topLeft()));
	int startY = max(0, getYTileIndexFromCoordinate(area.topLeft()));
	int stopX = max(0, getXTileIndexFromCoordinate(area.bottomRight()));
	int stopY = max(0, getYTileIndexFromCoordinate(area.bottomRight()));

	stopX = min(stopX, (m_width -1));
	stopY = min(stopY, (m_height - 1));
	startX = min(startX, stopX);
	startY = min(startY, stopY);

	float tileWidth = m_terrainTileTypes.GetTileWidth();
	float tileHeight = m_terrainTileTypes.GetTileHeight();

	// Screen coordinates. Will be updated for every tile checked.
	// The first will most likely start at negative values.
	
	float y = (startY * tileHeight);
	for (int y_index = startY; y_index <= stopY; y_index++)
	{
		float x = (startX * tileWidth);
		for (int x_index = startX; x_index <= stopX; x_index++)
		{
			tile = getTile(x_index, y_index);
			if (tile != 0)
			{
				
				rect = tile->getRect();
				if (rect.bottomRight().x != 0 || rect.bottomRight().y != 0)
				{
					rect.offset(x,y);
					if ( bgo->collide(physComp, rect) )
						return true;
				}
				x += tileWidth;
			}
		}
		y += tileHeight;
	}

	return false;
}