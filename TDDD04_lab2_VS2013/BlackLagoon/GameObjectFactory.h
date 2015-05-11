#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "stdafx.h"
#include "IGameObjectFactory.h"
#include "BasicGameObject.h"
#include "GameObject.h"
#include "Player.h"
#include "PlayerAI.h"
#include "Shot.h"
#include "GunBoat.h"
#include "GunTurret.h"
#include "GunTurretAI.h"
#include "GunBoatAI.h"
#include "IInputDevice.h"

class GameObjectFactory : public IGameObjectFactory
{
public:
	GameObjectFactory(HTEXTURE gameObjectTextureAtlas);
	~GameObjectFactory();

	virtual Player* getPlayer(IInputDevice* input);
	virtual GameObject* getEnemy(int type);
	virtual SpecialGameObject* getSpecialObject(int type);
	virtual Shot* getPlayerShot();
	virtual Shot* getEnemyShot();

	virtual void release(SpecialGameObject*& bgo);
	virtual void release(GameObject*& go);
	virtual void release(Player*& player);
	virtual void release(Shot*& shot);

private:
	hgeSprite*	m_playerSprite;

	hgeSprite*	m_playerShotSprite;
	hgeSprite*	m_enemyShotSprite;

	hgeSprite*	m_enemySprites[NR_OF_ENEMY_TYPES];
	hgeSprite*	m_specialObjectSprites[NR_OF_SPECIAL_OBJECT_TYPES];
	hgeSprite*	m_buildingSprites[NR_OF_BUILDING_TYPES];

	std::vector<BasicGameObject*> m_objects;

};

#endif;