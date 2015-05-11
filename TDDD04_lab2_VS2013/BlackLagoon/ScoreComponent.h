#ifndef SCORE_COMPONENT_H
#define SCORE_COMPONENT_H

#include "stdafx.h"
#include "Player.h"
#include "IScoreComponent.h"

/*
The component is used to keep the player's score
The score increases when killing enemies
or when leveling up (levelup).
Reset allows the player to start at a higher level than 1 
but without gaining points for the higher level.
*/


class ScoreComponent : public IScoreComponent
{
public:
	ScoreComponent(hgeSprite* background, hgeFont* font, Player* player = 0);
public:
	~ScoreComponent();

public:
	virtual void setPlayer(Player* player);

	virtual int addScore(int score);
	virtual int getScore();
	virtual void levelUp();
	
	virtual float getTime();
	virtual float setTime(float time);

	virtual int addEnemyKill(int n = 1);
	virtual int getNrOfEnemiesKilled();

	// Reset the component
	virtual void reset();

	virtual void render(float x, float y);

private:
	int			m_score;
	float		m_time;
	int			m_nrOfEnemiesKilled;
	
	hgeSprite*	m_sprite;
	hgeFont*	m_font;
	Player*		m_player;
};

#endif