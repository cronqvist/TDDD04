#pragma once

class IMenuComponent
{
public:
	~IMenuComponent(){};
	enum MenuStates{PLAY=0, HIGHSCORE, SHOWCREDITS, EXIT};

	virtual void previous() = 0;
	virtual void next() = 0;
	virtual MenuStates select() = 0;
	virtual void render(float x, float y) = 0;
	virtual void reset() = 0;
};