#pragma once

#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include "SDL.h"
#include "Commons.h"

class GameScreen; //forward declares the use of the GameScreen class, basically a promise that we will add the GameScreen.h file in the cpp file

class GameScreenManager {
private:
	SDL_Renderer* mRenderer; //the renderer
	GameScreen* mCurrentScreen; //the current screen to be rendered

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen); //sets the renderer variable and the startScreen this will be main menu on the final game
	~GameScreenManager();

	void Render(); //renders the current screen
	void Update(float deltaTime, SDL_Event event); //updates the current screen

	void ChangeScreen(SCREENS newScreen); //changes to a new screen

};

#endif