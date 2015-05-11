#pragma once

#include "hgeSprite.h"

class ITileSprites
{
public:
	virtual ~ITileSprites(){};
	virtual hgeSprite* GetFull1()=0;
	virtual hgeSprite* GetFull2()=0;
	virtual hgeSprite* GetFull3()=0;
	virtual hgeSprite* GetHalf1()=0;
	virtual hgeSprite* GetHalf2()=0;
	virtual hgeSprite* GetIsland()=0;
	virtual hgeSprite* GetThreeQuarters()=0;
	virtual hgeSprite* GetOneQuarter()=0;
	virtual hgeSprite* GetBlank()=0;
	virtual float GetTileWidth()=0;
	virtual float GetTileHeight()=0;
};