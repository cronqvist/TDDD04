#ifndef GAME_H
#define GAME_H

#include "stdafx.h"

#include "IGameWorld.h"
#include "IMenuComponent.h"
#include "HighScoreComponent.h"
#include "CreditComponent.h"
#include "ILevelManager.h"
#include "IInputDevice.h"

class Game
{
public:
	enum States{MENU=0, RESET, LEVELINFO, LEVELCREATION , PLAY, ENDGAME, HIGHSCORE, ENDCREDITS};

	Game(HGE* gfw,
		IGameWorld* gameWorld,
		IMenuComponent*	menuComponent,
		IHighScoreComponent* highScoreComponent,
		ICreditComponent* creditComponent,
		ILevelManager*	levelManager,
		IInputDevice* inputDevice,
		hgeFont* font,
		States state
		);
	~Game();

public:
	char* getErrorMessage();

	bool updateGame();
	bool renderGame();
	
	void levelUp();
	void endGamePlay();
	
	void changeState(States newState);

private:	
	bool updateGame_menu(float deltaTime);
	bool updateGame_reset(float deltaTime);
	bool updateGame_levelInfo(float deltaTime);
	bool updateGame_levelCreation(float deltaTime);
	bool updateGame_play(float deltaTime);
	bool updateGame_endGame(float deltaTime);
	bool updateGame_highScore(float deltaTime);
	bool updateGame_endCredits(float deltaTime);

	bool renderGame_menu();
	bool renderGame_reset();
	bool renderGame_levelInfo();
	bool renderGame_levelCreation();
	bool renderGame_play();
	bool renderGame_endGame();
	bool renderGame_highScore();
	bool renderGame_endCredits();

	void displayInfo();

private:
	//gfw : Graphic frameWork
	HGE* m_gfw;

	float m_delayedTime;
	States m_state;

	IGameWorld* m_gameWorld;

	IMenuComponent*	m_menuComponent;
	IHighScoreComponent* m_highScoreComponent;
	ICreditComponent* m_creditComponent;
	ILevelManager*	m_levelManager;
	IInputDevice* m_inputDevice;

	hgeFont* m_font;
	bool m_displayInfo;
};

#endif