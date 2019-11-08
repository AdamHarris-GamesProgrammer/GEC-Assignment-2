#pragma once

#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"

class Texture2D; //forward declares, basically says we will include it in the CPP file this allows us to make reference to it here

class GameScreenMenu : GameScreen {
private:
	Texture2D* mBackgroundTexture; //we can use this as we forward declared the use of the Texture2D class

	bool SetUpLevel(); //sets up the level
public:
	GameScreenMenu(SDL_Renderer* renderer); 
	~GameScreenMenu();

	void Render(); //renders the screen
	void Update(float deltaTime, SDL_Event event); //updates the screen
};

#endif