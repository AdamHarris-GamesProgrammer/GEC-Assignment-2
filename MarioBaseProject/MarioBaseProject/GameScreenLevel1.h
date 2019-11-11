#pragma once

#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"

class Texture2D; //forward declares, basically says we will include it in the CPP file this allows us to make reference to it here
class Character;

class GameScreenLevel1 : GameScreen {
private:
	Texture2D* mBackgroundTexture; //we can use this as we forward declared the use of the Texture2D class
	Character* myCharacter;

	bool SetUpLevel(); //sets up the level
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render(); //renders the level
	void Update(float deltaTime, SDL_Event event); //updates the level
};

#endif