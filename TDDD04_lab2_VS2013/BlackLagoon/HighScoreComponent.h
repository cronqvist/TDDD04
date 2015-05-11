#ifndef HIGH_SCORE_COMPONENT_H
#define HIGH_SCORE_COMPONENT_H

#include "stdafx.h"
#include "IHighScoreComponent.h"
#include <vector>

#define NR_OF_SCORES 10

class HighScoreComponent : public IHighScoreComponent
{
public:
	HighScoreComponent(hgeSprite* background, 
		hgeFont* font, 
		hgeFont* fontSelected, 
		hgeFont* fontTitle,
		hgeFont* fontTitleShadow,
		const char* filename = 0,
		unsigned int nrOfScores = NR_OF_SCORES
		);
	~HighScoreComponent();

public:
	void submitScore(int score);

	bool readFromFile(const char * filename = 0);
	bool writeToFile(const char * filename = 0);

	void render(float x, float y);

	const std::vector<int>& scores();
	int lastScoreIndex();
private:
	void renderScore(float x, float y, const char* format, int nr, int score, bool selected);
	void renderTitle(float x, float y, const char* format);

private:
	hgeSprite*	m_sprite;
	hgeFont*	m_font;
	hgeFont*	m_fontSelected;
	hgeFont*	m_fontTitleShadow;
	hgeFont*	m_fontTitle;
	const char*	m_filename;

	/*
	m_lastScoreIndex is a zero-based index indicating what position
	in the highscore list should be highlighted as the last entered score
	m_lastScoreIndex = -1 indicate that no score will be highlighted when rendered.
	*/
	size_t		m_lastScoreIndex;
	std::vector<int>	m_scores;
	unsigned int m_nrOfScores;
	
};

#endif