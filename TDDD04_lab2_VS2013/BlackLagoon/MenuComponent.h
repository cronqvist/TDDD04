#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include "stdafx.h"
#include "IMenuComponent.h"

class MenuComponent: public IMenuComponent
{
public:
	MenuComponent(hgeSprite* background, hgeFont* font, hgeFont* fontShadow, hgeFont* fontSelected);
	~MenuComponent();

public:
	void previous();
	void next();
	MenuStates select();
	
	void render(float x, float y);
	void reset();

private:
	void renderFont(float x, float y, const char* format, bool selected);

private:
	hgeSprite* m_sprite;
	hgeFont* m_font;
	hgeFont* m_fontShadow;
	hgeFont* m_fontSelected;
	MenuStates m_state;

};

#endif