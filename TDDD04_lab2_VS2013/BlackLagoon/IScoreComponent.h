#pragma once

class IScoreComponent
{
public:
	virtual ~IScoreComponent(){};
	
	virtual void setPlayer(Player *player) = 0;
	virtual int addScore(int score) = 0;
	virtual void levelUp() = 0;
	virtual int getScore() = 0;
	virtual float getTime() = 0;
	virtual float setTime(float time) = 0;
	virtual int addEnemyKill(int n = 1) = 0;
	virtual int getNrOfEnemiesKilled() = 0;
	virtual void reset() = 0;
	virtual void render(float x, float y) = 0;
};