#ifndef CREDIT_COMPONENT_H
#define CREDIT_COMPONENT_H

#include "stdafx.h"
#include "ICreditComponent.h"

class CreditComponent : public ICreditComponent
{
public:
	CreditComponent(HTEXTURE texture);
	CreditComponent(hgeSprite* background, hgeFont* font);
	~CreditComponent();

public:
	void render(float x, float y);

private:
	hgeSprite* m_sprite;
	hgeFont* m_font;
};

#endif