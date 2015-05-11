#include "Game.h"

Game::Game(HGE* gfw,
		IGameWorld* gameWorld,
		IMenuComponent* menuComponent,
		IHighScoreComponent* highScoreComponent,
		ICreditComponent* creditComponent,
		ILevelManager* levelManager,
		IInputDevice* inputDevice,
		hgeFont* font,
		States state
		) :
	m_gfw(gfw),
	m_gameWorld(gameWorld),
	m_menuComponent(menuComponent),
	m_highScoreComponent(highScoreComponent),
	m_creditComponent(creditComponent),
	m_levelManager(levelManager),
	m_inputDevice(inputDevice),
	m_font(font),
	m_delayedTime(0.0f),
	m_state(state),
	m_displayInfo(false)
{
}

Game::~Game()
{
}

char* Game::getErrorMessage()
{
	return m_gfw->System_GetErrorMessage();
}

//return true to exit game
bool Game::updateGame()
{
	// Toggle display info on 'i'
	if (m_inputDevice->displayInfo())
	{
		m_displayInfo = !m_displayInfo;
	}

	float deltaTime = m_gfw->Timer_GetDelta();

	switch (m_state) {
		case Game::MENU:
			return updateGame_menu(deltaTime);
			break;
		case Game::RESET:
			return updateGame_reset(deltaTime);
			break;
		case Game::LEVELINFO:
			return updateGame_levelInfo(deltaTime);
			break;
		case Game::LEVELCREATION:
			return updateGame_levelCreation(deltaTime);
			break;
		case Game::PLAY:
			return updateGame_play(deltaTime);
			break;
		case Game::ENDGAME:
			return updateGame_endGame(deltaTime);
			break;
		case Game::HIGHSCORE:
			return updateGame_highScore(deltaTime);
			break;
		case Game::ENDCREDITS:
			return updateGame_endCredits(deltaTime);
			break;
	}
	return true;
}

//runs every render cycle
bool Game::renderGame()
{
	bool result;

	m_gfw->Gfx_BeginScene();

	switch (m_state) {
		case Game::MENU:
			result = renderGame_menu();
			break;
		case Game::RESET:
			result = renderGame_reset();
			break;
		case Game::LEVELINFO:
			result = renderGame_levelInfo();
			break;
		case Game::LEVELCREATION:
			result = renderGame_levelCreation();
			break;
		case Game::PLAY:
			result = renderGame_play();
			break;
		case Game::ENDGAME:
			result = renderGame_endGame();
			break;
		case Game::HIGHSCORE:
			result = renderGame_highScore();
			break;
		case Game::ENDCREDITS:
			result = renderGame_endCredits();
			break;

		default:
			result = false;
			break;
	}

	if (m_displayInfo)
		displayInfo();

	m_gfw->Gfx_EndScene();
	return result;
}

void Game::displayInfo()
{
	m_font->printf(10, 10, HGETEXT_LEFT, "FPS: %d", m_gfw->Timer_GetFPS());	
	m_font->printf(140, 10, HGETEXT_LEFT, "TIME: %3.3f", m_gameWorld->getGameTime());
	if (m_gameWorld->getGamePaused())
		m_font->printf(335, 10, HGETEXT_LEFT, "P");
}

//Return true to exit the game
bool Game::updateGame_menu(float deltaTime)
{
	// Exit Game Application on Escape
	if(m_inputDevice->exit())
	{
		return true;
	}

	if(m_inputDevice->next())
	{
		m_menuComponent->next();
	}
	if(m_inputDevice->previously())
	{
		m_menuComponent->previous();
	}
	if(m_inputDevice->select())
	{
		switch (m_menuComponent->select()) {
			case m_menuComponent->PLAY:
				changeState(Game::RESET);
				break;
			case m_menuComponent->HIGHSCORE:
				changeState(Game::HIGHSCORE);
				break;
			case m_menuComponent->SHOWCREDITS:
				changeState(Game::ENDCREDITS);
				break;
			case m_menuComponent->EXIT:
				break;
		}
	}
	return false;
}

bool Game::renderGame_menu()
{
	// 0xAARRGGBB <-- Alpha, Red, Green, Blue
	m_gfw->Gfx_Clear(0xff111111);
	m_menuComponent->render(0.0f,0.0f);
	return false;
}

bool Game::updateGame_reset(float deltaTime)
{
	//Reset for new game
	m_levelManager->reset();
	m_gameWorld->reset();
	changeState(Game::LEVELINFO);
	return false;
}

bool Game::renderGame_reset()
{
	m_gfw->Gfx_Clear(0xff111111);
	return false;
}

bool Game::updateGame_levelInfo(float deltaTime)
{
	//Do nothing except reset deltaTime and set next state;

	if (m_levelManager->lastLevel())
	{
		changeState(Game::ENDGAME);
		return false;
	}

	m_state  = Game::LEVELCREATION;

	return false;
}

bool Game::renderGame_levelInfo()
{
	m_gfw->Gfx_Clear(0xff111111);
	m_levelManager->render(0.0f,0.0f);
	return false;
}

bool Game::updateGame_levelCreation(float deltaTime)
{
	if (m_delayedTime == 0)
	{
		// Load Level - setup Game Object Manager and Terrain Manager
		//m_levelManager->loadLevel(m_gameObjectManager, m_terrainManager);
		m_gameWorld->loadLevel(m_levelManager);
	}
	
	// Show info for a few seconds
	if (m_delayedTime > 1.0f)
	{
		changeState(Game::PLAY);
	}
	else
	{
		m_delayedTime += deltaTime;
	}

	return false;
}

bool Game::renderGame_levelCreation()
{
	//Do nothing, leave the screen as it was from levelInfo.
	return false;
}

bool Game::updateGame_highScore(float deltaTime)
{	
	if(m_inputDevice->exit() || m_inputDevice->select())
	{
		changeState(Game::MENU);
	}	
	return false;
}

bool Game::renderGame_highScore()
{
	m_gfw->Gfx_Clear(0xff111111);
	m_highScoreComponent->render(0.0f,0.0f);
	return false;
}

bool Game::updateGame_endCredits(float deltaTime)
{
	if(m_inputDevice->exit() || m_inputDevice->select())
	{
		changeState(Game::MENU);
	}	
	return false;
}

bool Game::renderGame_endCredits()
{
	m_gfw->Gfx_Clear(0xff111111);
	m_creditComponent->render(0.0f,0.0f);
	return false;
}

bool Game::updateGame_endGame(float deltaTime)
{
	m_highScoreComponent->submitScore(m_gameWorld->getScore());
	m_highScoreComponent->writeToFile();
	
	changeState(Game::HIGHSCORE);
	return false;
}

bool Game::renderGame_endGame()
{
	m_gfw->Gfx_Clear(0xff111111);
	return false;
}

bool Game::updateGame_play(float deltaTime)
{
	// Exit game play and return to menu on Escape
	if(m_inputDevice->exit())
	{
		endGamePlay();
		return false;
	}

	// Pause game world on 'p'
	if(m_inputDevice->pause())
	{
		m_gameWorld->toggleGamePaused();
	}

	m_gameWorld->tick(deltaTime);

	return false;
}

bool Game::renderGame_play()
{
	// Clear screen with blue color
	// 0xAARRGGBB <-- Alpha, Red, Green, Blue
	m_gfw->Gfx_Clear(0xff222222);
	m_gameWorld->render();
	return false;
}

void Game::levelUp()
{
	m_levelManager->levelUp();
	changeState(Game::LEVELINFO);
}

void Game::endGamePlay()
{
	changeState(Game::ENDGAME);
}

void Game::changeState(States newState)
{
	m_delayedTime = 0.0f;
	m_state = newState;
}