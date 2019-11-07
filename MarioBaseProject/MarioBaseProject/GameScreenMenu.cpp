#include "GameScreenMenu.h"
#include <iostream>
#include "Texture2D.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer): GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenMenu::~GameScreenMenu()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenMenu::Update(float deltaTime, SDL_Event event)
{

}

void GameScreenMenu::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

bool GameScreenMenu::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/menu.png")) {
		std::cout << "Failed to load background texture!";
		return false;
	}
	else {
		return true;
	}
}

