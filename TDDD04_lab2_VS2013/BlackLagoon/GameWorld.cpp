#include "GameWorld.h"
#include "player.h"
#include "gameobject.h"
#include "SpecialGameObject.h"
#include "GameObjectTypeDefinitions.h"

GameWorld::GameWorld(IGameWorldEvent* playerDied, 
		IGameWorldEvent* levelUp,
		IGameObjectManager* gameObjectManager, 
		IPhysicsComponent* physicsComponent,
		IScoreComponent* scoreComponent,
		ITerrainManager* terrainManager,
		IInputDevice* inputDevice,
		Rect cameraView)
	: 
	m_eventPlayerDied(playerDied), 
	m_eventLevelUp(levelUp), 
	m_gameObjectManager(gameObjectManager),
	m_physicsComponent(physicsComponent),
	m_scoreComponent(scoreComponent),
	m_terrainManager(terrainManager),
	m_inputDevice(inputDevice),
	m_cameraView(cameraView),
	m_timeRest(0.0f),
	m_gameTime(0.0f),
	m_gamePaused(false)
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::reset()
{
	m_gameObjectManager->reset();
	m_scoreComponent->reset();
	
	m_gamePaused = false;

	m_timeRest = 0.0f;
	m_gameTime = 0.0f;
	m_cameraView.moveTo(Coord(0.0f, 0.0f));

	m_gameObjectManager->reset();
	m_scoreComponent->reset();

	// Add a player to the world and set health, money and ammo
	m_gameObjectManager->addPlayer(m_inputDevice)->setStats(100, 100, 100);

	// Set player to show on score board
	m_scoreComponent->setPlayer(m_gameObjectManager->getPlayer());
}

void GameWorld::loadLevel(ILevelManager* levelManager)
{
	levelManager->loadLevel(m_gameObjectManager, m_terrainManager);

	// Set Camera to the bottom-middle of the terrain
	m_cameraView.bottomRight().x = (m_terrainManager->getPixelWidth() / 2.0f) + 
		(PLAY_AREA_WIDTH / 2.0f);
	m_cameraView.bottomRight().y = (m_terrainManager->getPixelHeight());
	m_cameraView.topLeft().x = m_cameraView.bottomRight().x - PLAY_AREA_WIDTH;
	m_cameraView.topLeft().y = m_cameraView.bottomRight().y - PLAY_AREA_HEIGHT;
}

void GameWorld::render()
{
	m_terrainManager->render(m_cameraView);
	m_gameObjectManager->render(m_cameraView);
	m_scoreComponent->render(600,0);
}

int GameWorld::getScore()
{
	return m_scoreComponent->getScore();
}

void GameWorld::setGamePaused(bool pause)
{
	m_gamePaused = pause;
}

bool GameWorld::getGamePaused()
{
	return m_gamePaused;
}

void GameWorld::toggleGamePaused()
{
	m_gamePaused = !m_gamePaused;
}

float GameWorld::getGameTime()
{
	return m_gameTime;
}

void GameWorld::updateGameTime(float deltaTime)
{
	m_gameTime += deltaTime;
	m_scoreComponent->setTime(m_gameTime);
}

void GameWorld::tick(float deltaTime)
{
	if (m_gamePaused)
		return;

	updateGameTime(deltaTime);

	// Check if the player has fired a shot and tick the player object
	fireAndTickPlayer(deltaTime);

	// check active, fire and tick all enemy objects
	fireAndTickEnemies(deltaTime);
	
	// Runs physics simulation in small steps.
	physicsSimulation(deltaTime);
}

void GameWorld::fireAndTickPlayer(float deltaTime)
{
	Shot* shot = 0;
	Player* player = m_gameObjectManager->getPlayer();

	// Check for shots fired
	if (player->fire(deltaTime))
	{
		shot = m_gameObjectManager->addPlayerShot();
		player->setNewShot(shot);
	}
	// Tick player once
	player->tick(deltaTime, m_gameObjectManager);
}

void GameWorld::fireAndTickEnemies(float deltaTime)
{
	Shot* shot = 0;

	for (std::vector<GameObject*>::iterator it = m_gameObjectManager->Enemies().begin();
			it != m_gameObjectManager->Enemies().end(); it++)
	{

		// Check if enemy is in camera view range and hence active
		(*it)->setActive((*it)->collide(m_physicsComponent, m_cameraView));
		
		// Do stuff if active
		 if ((*it)->getActive())
		 {
			// Check if fire shot
			if((*it)->fire(deltaTime))
			{
				Shot* shot = m_gameObjectManager->addEnemyShot();
				(*it)->setNewShot(shot);
			}

			// Tick the enemy
			(*it)->tick(deltaTime, m_gameObjectManager);
		 }
	}
}

void GameWorld::physicsSimulation(float deltaTime)
{
	Player* player = m_gameObjectManager->getPlayer();

	// Move camera view
	bool cameraMoved = moveCamera(deltaTime);

	// Add time not used before
	deltaTime += m_timeRest;

	// If enough time for a tick have passed
	if (deltaTime > GAME_WORLD_EPS)
	{
		// Break down elapsed time in smaller chucks to get a smouth experience.
		for(; deltaTime > GAME_WORLD_EPS; deltaTime -= GAME_WORLD_EPS)
		{
			// Move player along with camera if camera has moved
			if (cameraMoved)
			{
				player->offsetPosition(Coord(0.0f, -CAMERA_MOVING_SPEED*GAME_WORLD_EPS));
			}

			// Move all objects
			m_physicsComponent->move(m_gameObjectManager, GAME_WORLD_EPS);

			// Move player back in view if outside camera view
			movePlayerBackIntoView(player);

			// Check for collisions
			checkForCollisions();
	
			//PLAYER DEAD
			if (player->isDead())
			{
				return;
			}
		}

		// Store any unused time
		m_timeRest = deltaTime;
	}
	else
	{
		m_timeRest = deltaTime;
	}
}

bool GameWorld::moveCamera(float deltaTime)
{
	if (m_cameraView.topLeft().y != 0)
	{
		m_cameraView.offset(0.0f, -CAMERA_MOVING_SPEED*deltaTime);
		
		if (m_cameraView.topLeft().y < 0)
		{
			m_cameraView.moveTo(Coord(0.0f, 0.0f));
		}
		
		return true;
	}

	return false;
}

void GameWorld::movePlayerBackIntoView(Player* player)
{
	Coord pos = player->getPosition();
	pos.x = max(pos.x, m_cameraView.topLeft().x);
	pos.y = max(pos.y, m_cameraView.topLeft().y);
	pos.x = min(pos.x, m_cameraView.bottomRight().x);
	pos.y = min(pos.y, m_cameraView.bottomRight().y);
	player->setPosition(pos);
}

void GameWorld::checkForCollisions()
{
	Player* player = m_gameObjectManager->getPlayer();

	// check enemies against player shots and against player.
	checkCollisionWithEnemies(player);

	// Player against special objects
	checkCollionPlayerVsSpecialObjects(player);

	// Enemy shots against player			
	checkCollisionVsEnemyShots(player);

	// Check if player collide with the terrain
	checkTerrainCollision(player);

}

void GameWorld::checkCollisionWithEnemies(Player* player)
{
	GameObject* enemy;
	SpecialGameObject* specObj;

	for (unsigned int i = 0; i < m_gameObjectManager->Enemies().size(); i ++)
	{
		enemy = m_gameObjectManager->Enemies()[i];

		// Enemy collide with player-shot
		checkCollisionVsPlayersShots(enemy);

		// Enemy collide with Player
		checkCollisionVsPlayer(enemy, player);

		// Check enemy health
		if (enemy->isDead())
		{
			m_scoreComponent->addEnemyKill(1);
			m_scoreComponent->addScore(10);
			if (enemy->Ammo != 0) {
				specObj = m_gameObjectManager->addSpecialObject(AMMO_TYPE);
				specObj->setPosition(enemy->getPosition());
			}
			if (enemy->Money != 0) {
				specObj = m_gameObjectManager->addSpecialObject(MONEY_TYPE);
				specObj->setPosition(enemy->getPosition());
			}

			m_gameObjectManager->removeEnemy(i);
			i--;
			continue;
		}
	}
}

void GameWorld::checkCollisionVsPlayer(GameObject* go, Player* player)
{
	if ( go->collide(m_physicsComponent, player->getRectangle()) )
	{
		// Move back
		player->move(m_physicsComponent, -GAME_WORLD_EPS*20);
		go->move(m_physicsComponent, -GAME_WORLD_EPS*20);
		
		// Collision Damage
		go->Health -= COLLISION_DAMAGE;
	}
}

void GameWorld::checkCollisionVsPlayersShots(GameObject* go)
{
	Shot* shot;
	for (int j = 0; j < m_gameObjectManager->getPlayerShotsInUse(); j ++)
	{
		shot = m_gameObjectManager->getPlayerShot(j);

		// Check that the shot is on screen. If not, remove.
		shot->setActive(shot->collide(m_physicsComponent, m_cameraView));
		if (!shot->getActive())
		{
			m_gameObjectManager->removePlayerShot(j);
			j--;
			continue;
		}

		// check if shot hits enemy.
		if ( shot->collide(m_physicsComponent, go->getRectangle()))
		{
			go->Health -= shot->Damage;
			m_gameObjectManager->removePlayerShot(j);
			j--;
			continue;
		}
	}
}

void GameWorld::checkCollionPlayerVsSpecialObjects(Player* player)
{
	SpecialGameObject* specObj;

	for (unsigned int i = 0; i < m_gameObjectManager->SpecialObjects().size(); i++)
	{
		specObj = m_gameObjectManager->SpecialObjects()[i];
		if ( specObj->collide(m_physicsComponent, player->getRectangle()) )
		{
			specObj->action(player);
			if (specObj->getType() == MARK_TYPE)
			{
				m_scoreComponent->levelUp();
				m_eventLevelUp->run();
			}

			m_gameObjectManager->removeSpecialObject(i);
			i--;
		}
	}
}

void GameWorld::checkCollisionVsEnemyShots(GameObject* go)
{
	Shot* shot;
	Rect goRect = go->getRectangle();

	for (int i = 0; i < m_gameObjectManager->getEnemyShotsInUse(); i++)
	{
		shot = m_gameObjectManager->getEnemyShot(i);

		// Check that the shot is on screen. If not, remove.
		shot->setActive(shot->collide(m_physicsComponent, m_cameraView));
		if (!shot->getActive())
		{
			m_gameObjectManager->removeEnemyShot(i);
			i--;
			continue;
		}

		if ( shot->collide(m_physicsComponent, goRect) )
		{
			go->Health -= shot->Damage;
			m_gameObjectManager->removeEnemyShot(i);
			i--;
			continue;
		}
	}
}

void GameWorld::checkTerrainCollision(GameObject* go)
{
	if ( m_terrainManager->checkCollision(m_physicsComponent, go, m_cameraView) )
	{
		//If collide, move time backwards to move away from terrain
		go->move(m_physicsComponent, -GAME_WORLD_EPS*40);
		go->Health -= COLLISION_DAMAGE;
	}
}