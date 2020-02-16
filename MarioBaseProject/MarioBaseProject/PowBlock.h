#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include "SDL.h"
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"

class PowBlock {
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* levelMap, Vector2D* position);
	~PowBlock();

	void Render();
	void TakeAHit();

	bool IsAvailable() { return mAvailable; }

	SDL_Rect* GetDestRect() { return mDestRect; }
	SDL_Rect* GetSrcRect() { return mSrcRect; }

private:
	SDL_Renderer* mRenderer;
	Vector2D* mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	SDL_Rect* mDestRect;
	SDL_Rect* mSrcRect;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	bool mAvailable = true;

	int mNumberOfHitsLeft;
};

#endif