#pragma once

class ICreditComponent
{
public:
	virtual ~ICreditComponent(){};
	virtual void render(float x, float y) = 0;
};