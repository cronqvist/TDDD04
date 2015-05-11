#pragma once
#include "igameworld.h"
#include "stdafx.h"
#include "IGameObjectManager.h"
#include "IPhysicsComponent.h"
#include "IScoreComponent.h"
#include "ITerrainManager.h"
#include "IGameWorldEvent.h"
#include "IInputDevice.h"
#include "Player.h"
#include "GameObject.h"

class GameWorld :
	public IGameWorld
{
public:
	GameWorld(IGameWorldEvent* playerDied, 
		IGameWorldEvent* levelUp,
		IGameObjectManager* gameObjectManager, 
		IPhysicsComponent* physicsComponent,
		IScoreComponent* scoreComponent,
		ITerrainManager* terrainManager,
		IInputDevice* inputDevice,
		Rect cameraView);
	~GameWorld();

	void tick(float deltaTime);
	void reset();
	void loadLevel(ILevelManager* levelManager);
	void render();
	int getScore();
	bool getGamePaused();
	void setGamePaused(bool pause);
	void toggleGamePaused();
	float getGameTime();

private:
	void updateGameTime(float deltaTime);
	bool moveCamera(float deltaTime);
	void movePlayerBackIntoView(Player* player);
	void fireAndTickPlayer(float deltaTime);
	void fireAndTickEnemies(float deltaTime);
	void physicsSimulation(float deltaTime);

	void checkForCollisions();
	void checkCollisionWithEnemies(Player* player);
	void checkCollisionVsPlayersShots(GameObject* go);
	void checkCollisionVsPlayer(GameObject* go, Player* player);
	void checkCollionPlayerVsSpecialObjects(Player* player);
	void checkTerrainCollision(GameObject* go);
	void checkCollisionVsEnemyShots(GameObject* go);

private:
	IGameWorldEvent* m_eventPlayerDied;
	IGameWorldEvent* m_eventLevelUp;

	IGameObjectManager* m_gameObjectManager;
	IPhysicsComponent* m_physicsComponent;
	IScoreComponent* m_scoreComponent;
	ITerrainManager* m_terrainManager;
	IInputDevice* m_inputDevice;

	bool m_gamePaused;
	float m_gameTime;
	Rect m_cameraView;
	float m_timeRest;	
};
