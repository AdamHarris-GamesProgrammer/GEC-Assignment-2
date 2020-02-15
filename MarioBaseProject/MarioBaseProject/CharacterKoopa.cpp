#include "CharacterKoopa.h"
#include "Constants.h"


CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* levelMap, Vector2D startPosition, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, levelMap)
{
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

void CharacterKoopa::FlipRightWayUp()
{
	mInjured = false;
	Jump();
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;

		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::Render()
{
	int left = 0.0f;

	if (mInjured) {
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpriteSheet = { left,0,mSingleSpriteWidth,mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpriteSheet, destRect, mFlipState);
}

void CharacterKoopa::Update(float deltaTime, SDL_Event eventHandler){

}

bool CharacterKoopa::GetAlive()
{
	return !mInjured;
}

void CharacterKoopa::SetAlive(bool aliveValue)
{
	mInjured = aliveValue;
}

