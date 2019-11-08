#pragma once

#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include "SDL.h"

class GameScreen {
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render(); //this is a virtual method meaning that sub classes will have there own code for this method
	virtual void Update(float deltaTime, SDL_Event event); //takes in a time and a event such as moving etc.
protected:
	SDL_Renderer* mRenderer; //the subclasses derived from this class can use the mRenderer variable but no classes that dont inherit from it can
private:

};
#endif // !_GAMESCREEN_H



