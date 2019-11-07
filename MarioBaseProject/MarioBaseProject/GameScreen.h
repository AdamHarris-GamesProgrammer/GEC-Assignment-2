#pragma once

#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include "SDL.h"

class GameScreen {
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event event);
protected:
	SDL_Renderer* mRenderer;
private:

};
#endif // !_GAMESCREEN_H



