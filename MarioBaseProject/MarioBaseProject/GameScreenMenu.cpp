#include "GameScreenMenu.h"
#include <iostream>
#include "Texture2D.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer): GameScreen(renderer)
{
	SetUpLevel(); //sets up the level as soon as the object is created
}

GameScreenMenu::~GameScreenMenu()
{
	//clears up memory
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenMenu::Update(float deltaTime, SDL_Event event){}

void GameScreenMenu::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE); //renders the background texture onto the screen
}

bool GameScreenMenu::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer); 
	if (!mBackgroundTexture->LoadFromFile("Images/menu.png")) { //loads the background image
		std::cout << "Failed to load background texture!"; //if it fails to load
		return false; //return false, program ends
	}
	else {
		return true; //return true, program continues
	}
}

