#include "PowBlock.h"
#include <iostream>

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* levelMap, Vector2D* position)
{
	std::string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str())) {
		std::cout << "Failed to load texture: " << imagePath << std::endl;
		return;
	}

	mLevelMap = levelMap;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = position;

	mDestRect = new SDL_Rect();
	mDestRect->x = mPosition->x;
	mDestRect->y = mPosition->y;
	mDestRect->w = mSingleSpriteWidth;
	mDestRect->h = mSingleSpriteHeight;

	mSrcRect = new SDL_Rect();
	mSrcRect->x = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);
	mSrcRect->y = 0;
	mSrcRect->w = TILE_WIDTH;
	mSrcRect->h = TILE_HEIGHT;
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;

	mLevelMap = NULL;
}

void PowBlock::Render()
{
	if (mAvailable) {
		mTexture->Render(*mSrcRect, *mDestRect, SDL_FLIP_NONE);
	}
}

void PowBlock::TakeAHit()
{
	if (mAvailable) {
		mNumberOfHitsLeft--;
		mSrcRect->x = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		if (mNumberOfHitsLeft <= 0) {

			mNumberOfHitsLeft = 0;
			mAvailable = false;
			mLevelMap->ChangeTileAt(mPosition->y / TILE_HEIGHT, mPosition->x / TILE_WIDTH, 0); 
			
		}
	}


}

