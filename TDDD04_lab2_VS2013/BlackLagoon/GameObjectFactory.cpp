#include "GameObjectFactory.h"
#include "Mark.h"
#include "Money.h"
#include "HealthPackage.h"
#include "Ammo.h"

GameObjectFactory::GameObjectFactory(HTEXTURE gameObjectTextureAtlas) :
	m_playerSprite(0),
	m_playerShotSprite(0),
	m_enemyShotSprite(0)
{
	m_playerSprite = new hgeSprite(gameObjectTextureAtlas, 2.0f, 2.0f, 78.0f, 44.0f);
	m_playerShotSprite = new hgeSprite(gameObjectTextureAtlas, 40.0f, 96.0f, 15.0f, 4.0f);
	m_enemyShotSprite = new hgeSprite(gameObjectTextureAtlas, 72.0f, 94.0f, 16.0f, 7.0f);

	// Boat
	m_enemySprites[0] = new hgeSprite(gameObjectTextureAtlas, 5.0f, 53.0f, 80.0f, 31.0f);
	// Gunboat
	m_enemySprites[1] = new hgeSprite(gameObjectTextureAtlas, 44.0f, 124.0f, 206.0f, 38.0f);
	//Boss
	m_enemySprites[2] = new hgeSprite(gameObjectTextureAtlas, 35.0f, 174.0f, 215.0f, 79.0f);
	// Gun turret
	m_enemySprites[3] = new hgeSprite(gameObjectTextureAtlas, 123.0f, 3.0f, 130.0f, 52.0f);
	// Gun turret for boat
	m_enemySprites[4] = new hgeSprite(gameObjectTextureAtlas, 176.0f, 61.0f, 76.0f, 30.0f);
	//m_enemySprites[x] = new hgeSprite(gameObjectTextureAtlas, 0.0f, 0.0f, 0.0f, 0.0f);

	// Mark
	m_specialObjectSprites[0] = new hgeSprite(gameObjectTextureAtlas, 7.0f, 113.0f, 14.0f, 16.0f);
	// Ammo
	m_specialObjectSprites[1] = new hgeSprite(gameObjectTextureAtlas, 4.0f, 142.0f, 15.0f, 35.0f);
	// Money
	m_specialObjectSprites[2] = new hgeSprite(gameObjectTextureAtlas, 4.0f, 188.0f, 21.0f, 26.0f);
	// Health
	m_specialObjectSprites[3] = new hgeSprite(gameObjectTextureAtlas, 6.0f, 226.0f, 23.0f, 23.0f);

	m_playerSprite->SetHotSpot(m_playerSprite->GetWidth()/2.0f, m_playerSprite->GetHeight()/2.0f);
	m_playerShotSprite->SetHotSpot(m_playerShotSprite->GetWidth()/2.0f, m_playerShotSprite->GetHeight()/2.0f);
	m_enemyShotSprite->SetHotSpot(m_enemyShotSprite->GetWidth()/2.0f, m_enemyShotSprite->GetHeight()/2.0f);

	for (int i = 0; i < NR_OF_ENEMY_TYPES; i++)
	{
		m_enemySprites[i]->SetHotSpot(m_enemySprites[i]->GetWidth()/2.0f, m_enemySprites[i]->GetHeight()/2.0f);
	}
	// Special hotspot for gunturrets
	m_enemySprites[GUN_TURRET_TYPE]->SetHotSpot(
		m_enemySprites[GUN_TURRET_TYPE]->GetWidth()/2.0f - 25,
		m_enemySprites[GUN_TURRET_TYPE]->GetHeight()/2.0f);
	m_enemySprites[GUN_TURRET_BOAT_TYPE]->SetHotSpot(
		m_enemySprites[GUN_TURRET_BOAT_TYPE]->GetWidth()/2.0f -10,
		m_enemySprites[GUN_TURRET_BOAT_TYPE]->GetHeight()/2.0f);

	for (int i = 0; i < NR_OF_SPECIAL_OBJECT_TYPES; i++)
	{
		m_specialObjectSprites[i]->SetHotSpot(m_specialObjectSprites[i]->GetWidth()/2.0f, m_specialObjectSprites[i]->GetHeight()/2.0f);
	}	

}

GameObjectFactory::~GameObjectFactory()
{
	SAFE_DELETE(m_playerSprite);
	SAFE_DELETE(m_playerShotSprite);
	SAFE_DELETE(m_enemyShotSprite);

	for (int i = 0; i < NR_OF_ENEMY_TYPES; i++)
	{
		SAFE_DELETE(m_enemySprites[i]);
	}
	for (int i = 0; i < NR_OF_SPECIAL_OBJECT_TYPES; i++)
	{
		SAFE_DELETE(m_specialObjectSprites[i]);
	}	
}

void GameObjectFactory::release(SpecialGameObject*& sgo)
{
	if (sgo) {
		sgo->destroy();
		sgo = 0;
	}
}

void GameObjectFactory::release(GameObject*& go)
{
	if (go) {
		go->destroy();
		go = 0;
	}
}

void GameObjectFactory::release(Shot*& shot)
{
	if (shot) {
		shot->destroy();
		shot = 0;
	}
}

void GameObjectFactory::release(Player*& player)
{
	if (player) {
		player->destroy();
		player = 0;
	}
}

Player* GameObjectFactory::getPlayer(IInputDevice* input)
{
	return new Player(m_playerSprite, new PlayerAI(input));
}

GameObject* GameObjectFactory::getEnemy(int type)
{
	GameObject* go;

	switch (type)
	{
		case BOAT_TYPE:
			go = new GameObject(m_enemySprites[BOAT_TYPE], new GunBoatAI());
			go->Money = 1;
			go->Health = 30;
			break;
		case GUN_BOAT_TYPE:
			go = new GunBoat(m_enemySprites[GUN_BOAT_TYPE], new GunBoatAI());
			static_cast<GunBoat*>(go)->setTurret(static_cast<GunTurret*>(getEnemy(GUN_TURRET_BOAT_TYPE)));
			go->Ammo = 1;
			go->Health = 80;
			break;
		case BOSS_TYPE:
			go = new GameObject(m_enemySprites[BOSS_TYPE], 0);
			go->Health = 500;
			break;
		case GUN_TURRET_TYPE:
			go = new GunTurret(m_enemySprites[GUN_TURRET_TYPE], new GunTurretAI());
			go->Health = 100;
			break;
		case GUN_TURRET_BOAT_TYPE:
			go = new GunTurret(m_enemySprites[GUN_TURRET_BOAT_TYPE], new GunTurretAI());
			go->Health = 50;
			break;
	}

	return go;
}

SpecialGameObject* GameObjectFactory::getSpecialObject(int type)
{
	SpecialGameObject* sgo;

	switch (type)
	{
		case MARK_TYPE:
			sgo = new Mark(m_specialObjectSprites[type], type);
			break;

		case AMMO_TYPE:
			sgo = new Ammo(20, m_specialObjectSprites[type], type);
			break;

		case MONEY_TYPE:
			sgo = new Money(100, m_specialObjectSprites[type], type);
			break;

		case HEALTH_TYPE:
			sgo = new HealthPackage(25, m_specialObjectSprites[type], type);
			break;
		
		default:
			throw std::exception("Invalid Special Game Object Type");
	}
	 
	sgo->setRotation(-M_PI_2);
	return sgo;
}

Shot* GameObjectFactory::getPlayerShot()
{
	return new Shot(m_playerShotSprite);
}

Shot* GameObjectFactory::getEnemyShot()
{
	return new Shot(m_enemyShotSprite);
}