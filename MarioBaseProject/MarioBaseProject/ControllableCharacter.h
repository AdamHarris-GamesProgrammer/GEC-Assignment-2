#pragma once
#include "Character.h"
class ControllableCharacter : public Character
{
public:
	ControllableCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* currentLevelMap) : Character(renderer, imagePath, startPosition, currentLevelMap) {}

	//void Update(float deltaTime, SDL_Event eventHandler) override;
	//void Render() override;
	virtual void PollInput(SDL_Event eventHandler);

protected:
	float mXVelocity = 0.0f;
	float mYVelocity = 0.0f;
};

