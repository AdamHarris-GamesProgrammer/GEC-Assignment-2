#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include "SDL.h"
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"

class PowBlock {
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* levelMap);
	~PowBlock();

	void Render();
	void TakeAHit();

	bool IsAvailable() { return mNumberOfHitsLeft > 0; }

	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight()); }

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;
};

#endif