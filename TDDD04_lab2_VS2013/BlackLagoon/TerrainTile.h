#ifndef TERRAINTILE_H
#define TERRAINTILE_H

#include "stdafx.h"

class TerrainTile
{
public:

	TerrainTile(hgeSprite* sprite, Rect rect, float rotation=0.0f, float hscale=1.0f, 
		float vscale=1.0f);
	~TerrainTile();

	void render(float x, float y);
	Rect getRect();
private:
	hgeSprite* m_sprite;
	float m_rotation;
	float m_hscale;
	float m_vscale;

	Rect m_rect;
};

#endif