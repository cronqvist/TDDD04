#include "ApplicationBuilder.h"
#include <assert.h>

#include "TerrainTileTypes.h"
#include "TileSprites.h"
#include "TerrainManager.h"
#include "LevelManager.h"
#include "PhysicsComponent.h"
#include "ScoreComponent.h"
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "MenuComponent.h"
#include "GameWorld.h"
#include "GameWorldEventPlayerDied.h"
#include "GameWorldEventLevelUp.h"
#include "HgeInputDevice.h"

#define NR_OF_TERRAIN_TILE_TYPES 21

ApplicationBuilder::ApplicationBuilder(HGE* hge) :
	gfw(hge),
	gameWorld(0),
	gameWorldEventPlayerDied(0),
	gameWorldEventLevelUp(0),
	inputDevice(0),
	scoreComponent(0),
	scoreComponentBackground(0),
	scoreComponentFont(0),
	menuComponent(0),
	menuComponentBackground(0),
	menuComponentFont(0),
	menuComponentFontShadow(0),
	menuComponentFontSelected(0),
	highScoreComponent(0),
	highScoreComponentBackground(0),
	highScoreComponentFont(0),
	highScoreComponentFontSelected(0),
	highScoreComponentFontTitle(0),
	highScoreComponentFontShadow(0),
	creditComponent(0),
	creditComponentBackground(0),
	creditComponentFont(0),
	levelManager(0),
	levelManagerBackground(0),
	levelManagerFont(0),
	levelManagerFontShadow(0),
	terrainManager(0),
	terrainTileTypes(0),
	tileSprites(0)
{
}

ApplicationBuilder::~ApplicationBuilder()
{
	SAFE_DELETE(scoreComponent);
	SAFE_DELETE(menuComponent);
	SAFE_DELETE(highScoreComponent);
	SAFE_DELETE(creditComponent);
	SAFE_DELETE(levelManager);
	SAFE_DELETE(gameObjectManager);
	SAFE_DELETE(gameObjectFactory);
	SAFE_DELETE(physicsComponent);
	SAFE_DELETE(gameWorld);
	SAFE_DELETE(gameWorldEventPlayerDied);
	SAFE_DELETE(gameWorldEventLevelUp);
	SAFE_DELETE(inputDevice);

	SAFE_DELETE(scoreComponentBackground);
	SAFE_DELETE(scoreComponentFont);

	SAFE_DELETE(menuComponentBackground);
	SAFE_DELETE(menuComponentFont);
	SAFE_DELETE(menuComponentFontShadow);
	SAFE_DELETE(menuComponentFontSelected);

	SAFE_DELETE(highScoreComponentBackground);
	SAFE_DELETE(highScoreComponentFont);
	SAFE_DELETE(highScoreComponentFontSelected);
	SAFE_DELETE(highScoreComponentFontTitle);
	SAFE_DELETE(highScoreComponentFontShadow);

	SAFE_DELETE(creditComponentBackground);
	SAFE_DELETE(creditComponentFont);

	SAFE_DELETE(terrainManager);
	SAFE_DELETE(terrainTileTypes);
	SAFE_DELETE(tileSprites);

	SAFE_DELETE(levelManagerBackground);
	SAFE_DELETE(levelManagerFont);
	SAFE_DELETE(levelManagerFontShadow);

	// Release textures
	if (terrainTexture != 0)
		gfw->Texture_Free(terrainTexture);
	if (scoreComponentTexture != 0)
		gfw->Texture_Free(scoreComponentTexture);
	if (menuTexture != 0)
		gfw->Texture_Free(menuTexture);
	if (backgroundTexture != 0)
		gfw->Texture_Free(backgroundTexture);
	if (gameObjectTexture != 0)
		gfw->Texture_Free(gameObjectTexture);
}

Game* ApplicationBuilder::buildGame()
{
	LoadTextures(this->gfw);

	Rect cameraView(Rect(0.0f,0.0f,600.0f,600.0f));

	tileSprites = new TileSprites(terrainTexture, 60.0f, 60.0f, 2.0f, 3.0f);
	terrainTileTypes = new TerrainTileTypes(tileSprites);
	terrainManager = new TerrainManager(terrainTileTypes);

	scoreComponent = buildScoreComponent(scoreComponentTexture, "fonts/BankGothic_Lt_BT_24.fnt");
	menuComponent = buildMenuComponent(menuTexture, "fonts/BankGothic_Lt_BT_64.fnt");
	highScoreComponent = buildHighScoreComponent(
			backgroundTexture, 
			"fonts/BankGothic_Md_BT_20.fnt",
			"fonts/BankGothic_Lt_BT_64.fnt",
			"highscore.txt");
	creditComponent = buildCreditComponent(backgroundTexture, "fonts/BankGothic_Lt_BT_20.fnt");
	levelManager = buildLevelManager(backgroundTexture, "levels/level.lev", 1);
	gameObjectFactory  = new GameObjectFactory(gameObjectTexture);
	gameObjectManager = new GameObjectManager(gameObjectFactory);
	
	physicsComponent = new PhysicsComponent();

	font = new hgeFont("fonts/BankGothic_Lt_BT_20.fnt");
	font->SetScale(1.0f);
	font->SetColor(ARGB(0xFF,0xFA,0xFA,0xA6));

	gameWorldEventPlayerDied = new GameWorldEventPlayerDied();
	gameWorldEventLevelUp = new GameWorldEventLevelUp();
	inputDevice = new HgeInputDevice(this->gfw);
	gameWorld = new GameWorld(gameWorldEventPlayerDied, 
		gameWorldEventLevelUp, 
		gameObjectManager, 
		physicsComponent,
		scoreComponent, 
		terrainManager,
		inputDevice,
		cameraView);

	Game* game = new Game(gfw, 
		gameWorld,
		menuComponent, 
		highScoreComponent, 
		creditComponent, 
		levelManager,
		inputDevice,
		font,
		Game::MENU);

	gameWorldEventPlayerDied->setGame(game);
	gameWorldEventLevelUp->setGame(game);

	return game;
}

void LevelUpGameEventHandler()
{

}

void ApplicationBuilder::LoadTextures(HGE* gfw)
{
	terrainTexture = gfw->Texture_Load("textures/terrain_texture_atlas.tga");;
	scoreComponentTexture = gfw->Texture_Load("textures/score_texture.tga");;
	menuTexture = gfw->Texture_Load("textures/menu_texture.tga");;
	backgroundTexture = gfw->Texture_Load("textures/background_texture.tga");
	gameObjectTexture = gfw->Texture_Load("textures/game_object_texture_atlas.tga");
}
IScoreComponent* ApplicationBuilder::buildScoreComponent(HTEXTURE texture, const char* fontFile)
{
	scoreComponentBackground = new hgeSprite(texture, 0.0f, 0.0f, 200, SCREEN_HEIGHT);
	scoreComponentFont = new hgeFont(fontFile);
	scoreComponentFont->SetScale(1.0f);
	scoreComponentFont->SetColor(ARGB(0xFF,0xFA,0xFA,0xA6));
	return new ScoreComponent(scoreComponentBackground, scoreComponentFont);
}

IMenuComponent* ApplicationBuilder::buildMenuComponent(HTEXTURE texture, const char* fontFile)
{
	menuComponentBackground = new hgeSprite(texture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

	menuComponentFont = new hgeFont(fontFile);
	menuComponentFont->SetScale(0.8f);
	menuComponentFont->SetColor(ARGB(0xA0,0xAF,0xAF,0xA0));

	menuComponentFontShadow = new hgeFont(fontFile);
	menuComponentFontShadow->SetScale(1.0f);
	menuComponentFontShadow->SetColor(ARGB(0xA0,0x10,10,10));

	menuComponentFontSelected = new hgeFont(fontFile);
	menuComponentFontSelected->SetScale(0.8f);
	menuComponentFontSelected->SetColor(ARGB(0xEE,145,21,23));

	return new MenuComponent(menuComponentBackground, menuComponentFont, menuComponentFontShadow, menuComponentFontSelected);
}

IHighScoreComponent* ApplicationBuilder::buildHighScoreComponent(HTEXTURE texture, 
		const char* fontFile, 
		const char* fontTitleFile,
		const char* highScoreFile
	)
{
	highScoreComponentBackground = new hgeSprite(texture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	highScoreComponentBackground->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	highScoreComponentBackground->SetColor(ARGB(255, 100,100,100));

	highScoreComponentFont = new hgeFont(fontFile);
	highScoreComponentFont->SetScale(1.0f);
	highScoreComponentFont->SetColor(ARGB(0xFA,0xAA,0xAA,0xA0));

	highScoreComponentFontSelected = new hgeFont(fontFile);
	highScoreComponentFontSelected->SetScale(1.0f);
	highScoreComponentFontSelected->SetColor(ARGB(0xEE,145,21,23));

	highScoreComponentFontTitle = new hgeFont(fontTitleFile);
	highScoreComponentFontTitle->SetScale(0.9f);
	highScoreComponentFontTitle->SetColor(ARGB(0xEE,145,21,23));

	highScoreComponentFontShadow = new hgeFont(fontTitleFile);
	highScoreComponentFontShadow->SetScale(1.0f);
	highScoreComponentFontShadow->SetColor(ARGB(0xA0,0x10,10,10));

	return new HighScoreComponent(highScoreComponentBackground, 
		highScoreComponentFont, 
		highScoreComponentFontSelected, 
		highScoreComponentFontTitle, 
		highScoreComponentFontShadow,
		highScoreFile
		);
}

ICreditComponent*
ApplicationBuilder::buildCreditComponent(HTEXTURE texture, const char* fontFile)
{
	creditComponentBackground = new hgeSprite(texture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	creditComponentBackground->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	creditComponentBackground->SetColor(ARGB(255, 100,100,100));

	creditComponentFont = new hgeFont(fontFile);
	creditComponentFont->SetScale(1.0f);
	creditComponentFont->SetColor(ARGB(0xFA,0xAA,0xAA,0xA0));

	return new CreditComponent(creditComponentBackground, creditComponentFont);
}

ILevelManager* ApplicationBuilder::buildLevelManager(HTEXTURE texture, const char* filename, int startingLevel)
{
	levelManagerBackground = new hgeSprite(texture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	levelManagerBackground->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	levelManagerBackground->SetColor(ARGB(255, 100,100,100));

	levelManagerFont = new hgeFont("fonts/BankGothic_Lt_BT_64.fnt");
	levelManagerFont->SetScale(0.9f);
	levelManagerFont->SetColor(ARGB(0xEE,145,21,23));

	levelManagerFontShadow = new hgeFont("fonts/BankGothic_Lt_BT_64.fnt");
	levelManagerFontShadow->SetScale(1.0f);
	levelManagerFontShadow->SetColor(ARGB(0xA0,0x10,10,10));

	return new LevelManager(levelManagerBackground, levelManagerFont, levelManagerFontShadow,
		filename, startingLevel);
}