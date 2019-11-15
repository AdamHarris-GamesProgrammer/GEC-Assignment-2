#pragma once

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"

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

	LevelMap* mCurrentLevelMap;

	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	float mCollisionRadius;

	void Jump();

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	void AddGravity(float deltaTime);
public:
	Character();
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	float GetCollisionRadius();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event eventHandler);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	Rect2D GetCollisionBox() {
		return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
	}

	Circle2D GetCollisionCircle() {
		return Circle2D(Vector2D(mPosition.x, mPosition.y), mCollisionRadius);
	}

	bool IsJumping() { return mJumping; }

	void CancelJump();
};

#endif