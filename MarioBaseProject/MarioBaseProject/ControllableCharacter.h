#pragma once
#include "Character.h"
class ControllableCharacter : public Character
{
public:
	ControllableCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* currentLevelMap) : Character(renderer, imagePath, startPosition, currentLevelMap) {}

	virtual void PollInput();

protected:
	float mXVelocity = 0.0f;
	float mYVelocity = 0.0f;
};

