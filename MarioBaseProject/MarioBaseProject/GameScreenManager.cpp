#include "GameScreenManager.h"
#include "GameScreen.h"

//need to include all of the level header files here to load them
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenMenu.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer; //sets the values
	mCurrentScreen = NULL; //clears the current screen
	ChangeScreen(startScreen); //changes the screen
}

GameScreenManager::~GameScreenManager()
{
	//handles the current memory
	mRenderer = NULL; 
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render(); //renders the current screen by calling its render method, mCurrentScreen is of type GameScreen and all levels inherit from that therefore this works for each level
}

void GameScreenManager::Update(float deltaTime, SDL_Event event)
{
	mCurrentScreen->Update(deltaTime, event);//updates the current screen by calling its update method, mCurrentScreen is of type GameScreen and all levels inherit from that therefore this works for each level
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen != NULL) { //if the currentScreen takes space in memory
		delete mCurrentScreen; //delete the memory
	}
	GameScreenLevel1* tempScreen; //sets a temp screen to be used by level 1
	GameScreenMenu* tempMenuScreen; //sets a temp screen to be used by the menu screen

	GameScreenLevel2* level2TempScreen;

	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		tempMenuScreen = new GameScreenMenu(mRenderer); //sets the tempMenuScreen variable equal to a new object of that class
		mCurrentScreen = (GameScreen*)tempMenuScreen; //sets the current screen equal to the temp screen
		tempMenuScreen = NULL; //deletes the temp screen
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_LEVEL2:
		level2TempScreen = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)level2TempScreen;
		level2TempScreen = NULL;
		break;
	case SCREEN_LEVEL3:

		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}

}
