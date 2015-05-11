/*

*/
#include "stdafx.h"
#include "ApplicationBuilder.h"
#include "Game.h"

// Placed in file global scope so that helper functions below has access to it.
Game* _game = 0;

namespace {

	//This function is called by the graphics framework
	bool renderGame()
	{
		return _game->renderGame();	
	}

	//This function is called by the graphics framework
	bool updateGame()
	{
		return _game->updateGame();
	}
}

HGE* InitGraphicFrameWork()
{
	HGE* gfw = hgeCreate(HGE_VERSION);
	gfw->System_SetState(HGE_FRAMEFUNC, updateGame);
	gfw->System_SetState(HGE_RENDERFUNC, renderGame);
	gfw->System_SetState(HGE_TITLE, "Black Lagoon");

	gfw->System_SetState(HGE_WINDOWED, true);
	gfw->System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
	gfw->System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
	gfw->System_SetState(HGE_SCREENBPP, 32);
	gfw->System_SetState(HGE_HIDEMOUSE, false);

	gfw->System_SetState(HGE_SHOWSPLASH, false);
	gfw->System_SetState(HGE_USESOUND, true);

	return gfw;
}

void ShutDownGraphicFrameWork(HGE* gfw)
{
	gfw->System_Shutdown();
	gfw->Release();
	gfw = 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	srand((unsigned)time(0));
	
	HGE* gfw = InitGraphicFrameWork();

	ApplicationBuilder* builder = new ApplicationBuilder(gfw);

	if (gfw->System_Initiate())
	{	
		_game = builder->buildGame();

		/*
		/ This starts the game.
		/ The graphics framework calls:
		/ updateGame()
		/ renderGame()
		/ over and over again, until updateGame returns true, then it exits
		/ and the execution here in main can continue.
		*/
		gfw->System_Start();
	}
	else 
	{
		// If Game initialization failed show error message
		MessageBox(0, _game->getErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	delete _game;
	delete builder;

	ShutDownGraphicFrameWork(gfw);

	return 0;

}
