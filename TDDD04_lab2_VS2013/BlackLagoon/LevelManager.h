#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "stdafx.h"
#include "ILevelManager.h"
#include "IGameObjectManager.h"
#include "IGameObjectFactory.h"
#include "ITerrainManager.h"
#include <fstream>

class LevelManager : public ILevelManager
{
public:
	LevelManager(hgeSprite* background, hgeFont* fontTitle, hgeFont* fontTitleShadow,
		const char* levelFileName, int startingLevel = 1);
	~LevelManager();

public:
	virtual void reset();
	virtual void setLevel(int level);
	virtual int getLevel();
	virtual int levelUp();
	virtual bool lastLevel();

	virtual void render(float x, float y);
	
	virtual void loadLevel(IGameObjectManager* GOM, ITerrainManager* TM, const char* filename = 0);
	void loadLevel(IGameObjectManager* GOM, ITerrainManager* TM, std::ifstream &f);

private:

	void renderTitle(float x, float y, const char* format, int level);

private:
	int			m_level;
	int			m_baseLevel;
	bool		m_lastLevel;
	const char* m_filename;

	hgeSprite*	m_sprite;
	hgeFont*	m_fontTitleShadow;
	hgeFont*	m_fontTitle;
};

#endif