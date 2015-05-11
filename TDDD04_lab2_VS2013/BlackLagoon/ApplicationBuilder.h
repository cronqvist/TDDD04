#pragma once

#include "stdafx.h"
#include "game.h"

#include "ITerrainManager.h"
#include "ITerrainTileTypes.h"
#include "TileSprites.h"
#include "ILevelManager.h"
#include "IGameObjectManager.h"
#include "IGameObjectFactory.h"
#include "IPhysicsComponent.h"
#include "IMenuComponent.h"
#include "ICreditComponent.h"
#include "IHighScoreComponent.h"
#include "IScoreComponent.h"
#include "IGameWorld.h"
#include "GameWorldEventPlayerDied.h"
#include "GameWorldEventLevelUp.h"
#include "IInputDevice.h"

class ApplicationBuilder
{

public:
	ApplicationBuilder(HGE* hge);
	~ApplicationBuilder();

	Game* buildGame();
	
private:
	void LoadTextures(HGE* gfw);

	IScoreComponent* buildScoreComponent(HTEXTURE texture, const char* fontFile);
	IMenuComponent* buildMenuComponent(HTEXTURE texture, const char* fontFile);
	IHighScoreComponent* buildHighScoreComponent(HTEXTURE texture, 
		const char* fontFile, 
		const char* fontTitleFile,
		const char* highScoreFile);

	ICreditComponent* buildCreditComponent(HTEXTURE texture, const char* fontFile);
	ILevelManager* buildLevelManager(HTEXTURE texture, const char* filename, int startingLevel);


private:
	HGE* gfw;

	HTEXTURE terrainTexture;	
	HTEXTURE scoreComponentTexture;
	HTEXTURE menuTexture;
	HTEXTURE backgroundTexture;
	HTEXTURE gameObjectTexture;

	IGameWorld* gameWorld;
	GameWorldEventLevelUp* gameWorldEventLevelUp;
	GameWorldEventPlayerDied* gameWorldEventPlayerDied;
	IInputDevice* inputDevice;

	IScoreComponent* scoreComponent;
	IMenuComponent* menuComponent;
	IHighScoreComponent* highScoreComponent;
	ICreditComponent* creditComponent;
	ILevelManager* levelManager;
	IGameObjectFactory* gameObjectFactory;
	IGameObjectManager* gameObjectManager;
	IPhysicsComponent* physicsComponent;

	hgeFont* font;

	hgeSprite* scoreComponentBackground;
	hgeFont* scoreComponentFont;

	hgeSprite* menuComponentBackground;
	hgeFont* menuComponentFont;
	hgeFont* menuComponentFontShadow;
	hgeFont* menuComponentFontSelected;

	hgeSprite* highScoreComponentBackground;
	hgeFont* highScoreComponentFont;
	hgeFont* highScoreComponentFontSelected;
	hgeFont* highScoreComponentFontTitle;
	hgeFont* highScoreComponentFontShadow;

	hgeSprite* creditComponentBackground;
	hgeFont* creditComponentFont;

	ITerrainManager* terrainManager;
	ITerrainTileTypes* terrainTileTypes;
	ITileSprites* tileSprites;

	hgeSprite* levelManagerBackground;
	hgeFont* levelManagerFont;
	hgeFont* levelManagerFontShadow;
};
