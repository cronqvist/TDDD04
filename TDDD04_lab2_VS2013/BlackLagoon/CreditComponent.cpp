#include "CreditComponent.h"

CreditComponent::CreditComponent(hgeSprite* background, hgeFont* font) :
	m_sprite(background),
		m_font(font)
{
}

CreditComponent::~CreditComponent()
{
}

void CreditComponent::render(float x, float y)
{
	m_sprite->Render(x, y);

	m_font->printfb(50, 50, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, HGETEXT_LEFT || HGETEXT_TOP,
		"Black Lagoon\nWritten by: Per Bohlin\nVersion: 1.01  Date: 2008-08-22 (reviced 2010-04-17)\n\nThe game was originally created as a part of a lab assignment in the course Introduction to game programming in C++, Blekinge Tekniska hogskola, Sweden, 2008\n\nIn 2010 the code was adopted to be used as a code skeleton for an assignement in the course TDDD04 Software Testing at Linkoping University\n\nPer Bohlin, 2010.");
}