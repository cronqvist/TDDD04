#include "TerrainTile.h"

TerrainTile::TerrainTile(hgeSprite* sprite, Rect rect, 
						 float rotation, float hscale, float vscale) :
	m_sprite(sprite),
	m_rect(rect),
	m_rotation(rotation),
	m_hscale(hscale),
	m_vscale(vscale)
{
}

TerrainTile::~TerrainTile()
{
}

void TerrainTile::render(float x, float y)
{
	float xOffset = 0;
	float yOffset = 0;
	m_sprite->GetHotSpot(&xOffset, &yOffset);
	m_sprite->RenderEx(x+xOffset, y + yOffset, m_rotation, m_hscale, m_vscale);
}

Rect TerrainTile::getRect()
{
	return m_rect;
}