#include "ScoreComponent.h"

// Determines the number of points gained from killing an alien
const int ENEMY_SCORE = 10;

//Determines the number of points gained from leveling up
const int LEVEL_SCORE = 100;

ScoreComponent::ScoreComponent(hgeSprite* background, hgeFont* font, Player* player) :
	m_sprite(background),
	m_font(font),
	m_player(player),
	m_score(0),
	m_time(0.0f),
	m_nrOfEnemiesKilled(0)
{
}

ScoreComponent::~ScoreComponent()
{
}

void ScoreComponent::setPlayer(Player* player)
{
	m_player = player;
}

int ScoreComponent::addScore(int score)
{
	m_score += score;
	return m_score;
}

int ScoreComponent::getScore()
{
	return m_score;
}

void ScoreComponent::levelUp()
{
	m_score += LEVEL_SCORE;
}

float ScoreComponent::getTime()
{
	return m_time;
}
float ScoreComponent::setTime(float time)
{
	m_time = time;
	return m_time;
}

int ScoreComponent::getNrOfEnemiesKilled()
{
	return m_nrOfEnemiesKilled;
}

int ScoreComponent::addEnemyKill(int n)
{
	m_nrOfEnemiesKilled += n;
	return m_nrOfEnemiesKilled;
}

void ScoreComponent::reset()
{
	m_nrOfEnemiesKilled = 0;
	m_time = 0.0f;
}

void ScoreComponent::render(float x, float y)
{
	m_sprite->Render(x, y);
	
	int sec = static_cast<int>(m_time);
	int minute = (sec / 60);
	int hr = (minute / 60);
	sec = sec % 60;
	minute = minute % 60;
	hr = hr % 24;
	
	m_font->printfb(x+30, y+78, 136,25, HGETEXT_RIGHT | HGETEXT_MIDDLE, "%i", m_score);
	if (m_player) {
		m_font->printfb(x+30, y+170, 136,25, HGETEXT_RIGHT | HGETEXT_MIDDLE, "%i", m_player->Money);
		m_font->printfb(x+30, y+261, 136,25, HGETEXT_RIGHT | HGETEXT_MIDDLE, "%i", m_player->Ammo);
		m_font->printfb(x+30, y+353, 136,25, HGETEXT_RIGHT | HGETEXT_MIDDLE, "%i", m_player->Health);
	} else {
		m_font->printfb(x+30, y+170, 136,25, HGETEXT_RIGHT | HGETEXT_MIDDLE, "n/a");
		m_font->printfb(x+30, y+261, 136,25, HGETEXT_RIGHT | HGETEXT_MIDDLE, "n/a");
		m_font->printfb(x+30, y+353, 136,25, HGETEXT_RIGHT | HGETEXT_MIDDLE, "n/a");
	}
	m_font->printfb(x+30, y+444, 136,25, HGETEXT_RIGHT | HGETEXT_MIDDLE, "%02i:%02i:%02i", hr, minute, sec);
	m_font->printfb(x+30, y+536, 136,25, HGETEXT_RIGHT | HGETEXT_MIDDLE, "%i", m_nrOfEnemiesKilled);

}