#include "MenuComponent.h"

MenuComponent::MenuComponent(hgeSprite* background, 
								hgeFont* font, 
								hgeFont* fontShadow, 
								hgeFont* fontSelected
								) :
		m_sprite(background),
		m_font(font),
		m_fontShadow(fontShadow),
		m_fontSelected(fontSelected),
		m_state(PLAY)
{
}


MenuComponent::~MenuComponent()
{
}

void MenuComponent::previous()
{
	switch (m_state) {
		case PLAY:
			m_state = EXIT;
			break;
		case HIGHSCORE:
			m_state = PLAY;
			break;
		case SHOWCREDITS:
			m_state = HIGHSCORE;
			break;
		case EXIT:
			m_state = SHOWCREDITS;
			break;
		default:
			m_state = PLAY;
			break;
	}
}

void MenuComponent::next()
{
	switch (m_state) {
		case PLAY:
			m_state = HIGHSCORE;
			break;
		case HIGHSCORE:
			m_state = SHOWCREDITS;
			break;
		case SHOWCREDITS:
			m_state = EXIT;
			break;
		case EXIT:
			m_state = PLAY;
			break;
		default:
			m_state = PLAY;
			break;
	}
}

MenuComponent::MenuStates MenuComponent::select()
{
	return m_state;
}

void MenuComponent::reset()
{
	m_state = PLAY;
}

void MenuComponent::renderFont(float x, float y, const char * format, bool selected)
{
	m_fontShadow->printfb(x+1, y+1, 410, 150, HGETEXT_LEFT | HGETEXT_TOP, format);
	m_font->printfb(x, y, 410, 150, HGETEXT_LEFT | HGETEXT_TOP, format);
	if (selected)
	{
		m_fontSelected->printfb(x, y, 410, 150, HGETEXT_LEFT | HGETEXT_TOP, format);
	}
}

void MenuComponent::render(float x, float y)
{
	m_sprite->Render(x, y);
	
	renderFont(x+172,y+67, "Play", (m_state == PLAY));
	renderFont(x+132, y+226, "High Score", (m_state == HIGHSCORE));
	renderFont(x+162, y+388, "Credits", (m_state == SHOWCREDITS));
	renderFont(x+660, y+434, "Exit", (m_state == EXIT));
}