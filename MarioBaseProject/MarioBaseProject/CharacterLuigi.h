#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"

class CharacterLuigi : public Character {
private:
	FACING mFacingDirection;

	bool mMovingRight;
	bool mMovingLeft;

public:
	void Render();
	void Update(float deltaTime, SDL_Event eventHandler);
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* levelMap);
	CharacterLuigi();

};


#endif // !_CHARACTERMARIO_H
#pragma once
