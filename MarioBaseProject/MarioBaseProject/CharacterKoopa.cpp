#include "CharacterKoopa.h"
#include "Constants.h"


CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* levelMap, Vector2D startPosition, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, levelMap)
{
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();

	mDestRect = new SDL_Rect();
	mDestRect->x = mPosition.x;
	mDestRect->y = mPosition.y;
	mDestRect->w = mSingleSpriteWidth;
	mDestRect->h = mSingleSpriteHeight;

	mSrcRect = new SDL_Rect();
	mSrcRect->x = 0;
	mSrcRect->y = 0;
	mSrcRect->w = TILE_WIDTH;
	mSrcRect->h = TILE_HEIGHT;
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
	mTexture->Render(*mSrcRect, *mDestRect, mFlipState);
}

void CharacterKoopa::Update(float deltaTime, SDL_Event eventHandler){
	float newXPos = GetPosition().x;
	float newYPos = GetPosition().y;

	int leftTile = newXPos / TILE_WIDTH;
	int rightTile = (newXPos + mTexture->GetWidth()) / TILE_WIDTH;
	int topTile = newYPos / TILE_HEIGHT;
	int bottomTile = (newYPos + mTexture->GetHeight()) / TILE_HEIGHT;


	if (bMovingRight) {
		newXPos += mMovementSpeed * deltaTime;

		//checks right tile collision
		if (mCurrentLevelMap->GetTileAt(bottomTile - 1, rightTile - 1) == 1 || mCurrentLevelMap->GetTileAt(bottomTile, rightTile -1 ) == 3) {
			newXPos = GetPosition().x;
			bMovingRight = false;
		}

	}
	else
	{
		newXPos -= mMovementSpeed * deltaTime;

		if (mCurrentLevelMap->GetTileAt(bottomTile - 1, leftTile) == 1 || mCurrentLevelMap->GetTileAt(bottomTile, leftTile) == 3) {
			newXPos = GetPosition().x;
			bMovingRight = true;
		}
	}

	//restrict X Position to screen bounds
	if (newXPos < 0 || newXPos + GetDestRect()->w > SCREEN_WIDTH) {
		newXPos = GetPosition().x;
		bMovingRight = !bMovingRight;
	}
	

	//orient sprite
	if (bMovingRight) {
		mFlipState = SDL_FLIP_NONE;
	}
	else
	{
		mFlipState = SDL_FLIP_HORIZONTAL;
	}


	SetPosition(Vector2D(newXPos, newYPos));
	mDestRect->x = mPosition.x;
	mDestRect->y = mPosition.y;
}

bool CharacterKoopa::GetAlive()
{
	return !mInjured;
}

void CharacterKoopa::SetAlive(bool aliveValue)
{
	mInjured = aliveValue;
}

