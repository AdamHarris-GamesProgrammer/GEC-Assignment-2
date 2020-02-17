#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"
#include <iostream>
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"

class CharacterKoopa : public Character {
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mInjuredTime;
	float mMovementSpeed;


	bool mInjured;

	void FlipRightWayUp();

	bool bMovingRight = true;

public:
	void TakeDamage();
	void Jump();

	void Render();
	void Update(float deltaTime, SDL_Event eventHandler);

	bool GetAlive();
	void SetAlive(bool aliveValue);

	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* levelMap, Vector2D startPosition, FACING startFacing, float movementSpeed);
};

#endif // !_CHARACTERKOOPA_H

