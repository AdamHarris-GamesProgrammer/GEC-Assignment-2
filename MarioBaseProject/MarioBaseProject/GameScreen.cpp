#include "GameScreen.h"


GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer; //sets the renderer
}

GameScreen::~GameScreen()
{
	mRenderer = NULL; //clears the renderer
}

void GameScreen::Render(){}

void GameScreen::Update(float deltaTime, SDL_Event event){}
