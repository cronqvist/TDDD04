#pragma once

#include <vector>

class IHighScoreComponent
{
public:
	virtual ~IHighScoreComponent(){};
	
	virtual void submitScore(int score) = 0;
	virtual bool readFromFile(const char * filename = 0) = 0;
	virtual bool writeToFile(const char * filename = 0) = 0;
	virtual void render(float x, float y) = 0;
	virtual const std::vector<int>& scores() = 0;
	virtual int lastScoreIndex() = 0;
};