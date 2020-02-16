#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMATIO_H

#include "ControllableCharacter.h"

class CharacterMario : public ControllableCharacter {
private:
	float mMovementSpeed = 5.0f;

public:
	void Update(float deltaTime, SDL_Event eventHandler) override;
	void PollInput() override;
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* levelMap);

	bool mCanJump = true;

};


#endif // !_CHARACTERMARIO_H
