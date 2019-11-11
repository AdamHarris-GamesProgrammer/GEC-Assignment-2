#pragma once

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "SDL.h"
#include <iostream>
#include "Commons.h"

class Texture2D;

class Character {
private:
	FACING mFacingDirection;

	bool mMovingRight;
	bool mMovingLeft;

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event eventHandler);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
};

#endif