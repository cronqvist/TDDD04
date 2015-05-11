#include "LevelManager.h"


#include <string>

LevelManager::LevelManager(hgeSprite* background, hgeFont* fontTitle, hgeFont* fontTitleShadow,
			 const char* levelFileName, int startingLevel) :
	m_sprite(background),
		m_fontTitle(fontTitle),
		m_fontTitleShadow(fontTitleShadow),
		m_filename(levelFileName),
		m_level(startingLevel),
		m_baseLevel(startingLevel),
		m_lastLevel(false)
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::reset()
{
	m_level = m_baseLevel;
	m_lastLevel = false;
}

int LevelManager::levelUp()
{
	return ++m_level;
}

void LevelManager::setLevel(int level)
{
	m_level = level;
}
int LevelManager::getLevel()
{
	return m_level;
}

bool LevelManager::lastLevel()
{
	return m_lastLevel;
}

void LevelManager::loadLevel(IGameObjectManager* GOM, ITerrainManager* TM, const char* filename)
{

	if (filename != 0)
		m_filename = filename;

	if (m_filename != 0)
	{
		std::ifstream f(m_filename);
		
		if (f.good())
		{
			loadLevel(GOM, TM, f);
			f.close();
		}
	}
}

void LevelManager::loadLevel(IGameObjectManager* GOM, ITerrainManager* TM, std::ifstream &f)
{
	std::string s;
	float x=0, y=0;
	float v_x, v_y;
	float rotation;
	int level = 0;
	int objType = 0;
	int nrOf = 0;
	GameObject* go = 0;
	BasicGameObject* bgo = 0;

	int terrainWidth;
	int terrainHeight;

	// Clear GOM for new level
	GOM->clearForNewLevel();

	//Find start of current level
	do {
		do {
		f >> s;
		} while(s != "[Level]" && f.good());
		f >> level;
	}	while (level != m_level && f.good());


	// Terrain Layout
	f >> s;
	if (s == "[TerrainLayout]")
	{

		f >> terrainWidth;
		f >> terrainHeight;
		int nrOfTiles = terrainWidth * terrainHeight;
		int* terrainLayout = new int[nrOfTiles];
		
		for(int i = 0; i < nrOfTiles; i++)
		{
			f >> terrainLayout[i];
		}
	
		TM->loadTerrain(terrainLayout, terrainWidth, terrainHeight);

		delete [] terrainLayout;
	}

	// Load Player
	f >> s;
	if (s == "[Player]")
	{
		f >> x;
		f >> y;
		f >> v_x;
		f >> v_y;
		f >> rotation;
		rotation *= M_PI;
		Player* player = GOM->getPlayer();
		player->setPosition(Coord(x,y));
		player->setVelocity(hgeVector(v_x, v_y));
		player->setRotation(rotation);
	}

	// Load enemies;
	f >> s;
	if (s == "[Enemies]")
	{

		f >> nrOf;

		for (int i = 0; i < nrOf; i++)
		{
			f >> objType;
			f >> x;
			f >> y;
			f >> v_x;
			f >> v_y;
			f >> rotation;
			rotation *= M_PI;
			go = GOM->addEnemy(objType);
			go->setPosition(Coord(x,y));
			go->setVelocity(hgeVector(v_x, v_y));
			go->setRotation(rotation);
		}
		
	}

	// Load Special objects

	f >> s;
	if (s == "[SpecialObjects]") 
	{
		f >> nrOf;
		for (int i = 0; i < nrOf; i++)
		{
			f >> objType;
			f >> x;
			f >> y;
			bgo = GOM->addSpecialObject(objType);
			bgo->setPosition(Coord(x, y));
		}
	}

	//Last Level?
	f >> s;
	if (s == "[LastLevel]") {
		f >> m_lastLevel;
	}
}

void LevelManager::renderTitle(float x, float y, const char * format, int level)
{
	m_fontTitleShadow->printfb(x+1, y+1, SCREEN_WIDTH, SCREEN_HEIGHT - 100, 
			HGETEXT_CENTER | HGETEXT_MIDDLE, format, level);
	m_fontTitle->printfb(x, y, SCREEN_WIDTH, SCREEN_HEIGHT - 100, 
			HGETEXT_CENTER | HGETEXT_MIDDLE, format, level);
}

void LevelManager::render(float x, float y)
{
	m_sprite->Render(x, y);

	// Title
	renderTitle(x, y, "Mission: %02i", m_level);

}