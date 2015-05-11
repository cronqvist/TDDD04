#include "HighScoreComponent.h"
#include <fstream>

using std::vector;

HighScoreComponent::HighScoreComponent(hgeSprite* background,
	hgeFont* font, 
	hgeFont* fontSelected, 
	hgeFont* fontTitle, 
	hgeFont* fontTitleShadow,
	const char* filename,
	unsigned int nrOfScores
	) :
		m_sprite(background),
		m_font(font),
		m_fontSelected(fontSelected),
		m_fontTitle(fontTitle),
		m_fontTitleShadow(fontTitleShadow),
		m_filename(filename),
		m_scores(vector<int>()),
		m_nrOfScores(nrOfScores)
{
	if (m_filename != 0)
		readFromFile();
}

HighScoreComponent::~HighScoreComponent()
{
}

void HighScoreComponent::submitScore(int score)
{
	m_lastScoreIndex = 0;

	m_scores.insert(m_scores.begin(), score);

	if (m_scores.size() > m_nrOfScores)
	{
		m_scores.pop_back();
	}

}

const vector<int>& HighScoreComponent::scores()
{
	return m_scores;
}

int HighScoreComponent::lastScoreIndex()
{
	return m_lastScoreIndex;
}

bool HighScoreComponent::readFromFile(const char * filename)
{
	if (filename != 0)
		m_filename = filename;

	if (m_filename != 0)
	{
		std::fstream f(m_filename, std::ios::in);

		if (f.good())
		{
			int tmp;

			m_scores.clear();

			do
			{
				f >> tmp;
				if (f.good())
				{
					m_scores.push_back(tmp);
				}
			} while (!f.fail());

			f.close();
		} else {
			return false;
		}

	} else {
		return false;
	}
	return true;
}
	

bool HighScoreComponent::writeToFile(const char * filename)
{
	if (filename != 0)
		m_filename = filename;

	if (m_filename != 0)
	{
		std::fstream f(m_filename, std::ios::out);

		for (vector<int>::iterator it = m_scores.begin(); it != m_scores.end(); it++)
		{
			f << *it << std::endl;
		}		
		f.close();

	} else {
		return false;
	}
	return true;
}

void HighScoreComponent::renderScore(float x, float y, const char * format, int nr, int score, bool selected)
{
	m_font->printfb(x, y, 410, 150, HGETEXT_LEFT | HGETEXT_TOP, format, nr, score);
	if (selected)
	{
		m_fontSelected->printfb(x, y, 410, 150, HGETEXT_LEFT | HGETEXT_TOP, format, nr, score);
	}

}

void HighScoreComponent::renderTitle(float x, float y, const char * format)
{
	m_fontTitleShadow->printfb(x+1, y+1, 410, 150, HGETEXT_LEFT | HGETEXT_TOP, format);
	m_fontTitle->printfb(x, y, 410, 150, HGETEXT_LEFT | HGETEXT_TOP, format);
}

void HighScoreComponent::render(float x, float y)
{
	m_sprite->Render(x, y);

	x += 150;
	y += 70;

	// Title
	renderTitle(x, y, "High Score");

	y += 60;
	x += 10;
	int scoreIndex = 0;
	int nr = 1;
	for (vector<int>::iterator it = m_scores.begin(); 
		it != m_scores.end(); it++, scoreIndex++, nr++)
	{
		y += 30;
		renderScore(x, y, "%i.  %i", nr, *it, (m_lastScoreIndex == scoreIndex));
	}
}