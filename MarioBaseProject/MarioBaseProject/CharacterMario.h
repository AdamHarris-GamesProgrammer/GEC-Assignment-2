#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMATIO_H

#include "Character.h"

class CharacterMario : public Character {
private:
	FACING mFacingDirection;
	CHARACTER_STATE mCharacterState;

	bool mMovingRight;
	bool mMovingLeft;

public:
	void Render();
	void Update(float deltaTime, SDL_Event eventHandler);
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* levelMap);
	CharacterMario();

	void SetState(CHARACTER_STATE state);

};


#endif // !_CHARACTERMARIO_H
