#include "Character.h"
#include "CharacterMario.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Commons.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* mCurrentLevelMap) : ControllableCharacter(renderer, imagePath, startPosition, mCurrentLevelMap)
{
	SetPosition(startPosition);
}

void CharacterMario::Update(float deltaTime, SDL_Event eventHandler)
{
	PollInput();

	float newXPos = GetPosition().x;
	float newYPos = GetPosition().y;


	if (mJumping) {
		mCanJump = false;

		//adjusts position
		newYPos -= mJumpForce * deltaTime;

		//reduces jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f) {
			mJumping = false;
		}
	}

	if (mXVelocity != 0.0f) {
		newXPos += mXVelocity * mMovementSpeed * deltaTime;
	}


	int leftTile = newXPos / TILE_WIDTH;
	int rightTile = (newXPos + mTexture->GetWidth()) / TILE_WIDTH;
	int topTile = newYPos / TILE_HEIGHT;
	int bottomTile = (newYPos + mTexture->GetHeight()) / TILE_HEIGHT;


	//left collision
	if (mCurrentLevelMap->GetTileAt(bottomTile -1, leftTile) != 0) {
		newXPos = GetPosition().x;
	}

	//right collision
	if (mCurrentLevelMap->GetTileAt(bottomTile-1, rightTile) != 0) {
		newXPos = GetPosition().x;
	}

	//foot collision
	if (mCurrentLevelMap->GetTileAt(bottomTile, rightTile) != 0 || mCurrentLevelMap->GetTileAt(bottomTile, leftTile) != 0) {
		mCanJump = true;
	}
	else {
		newYPos += GRAVITY * deltaTime;
	}

	//head collision
	if (mCurrentLevelMap->GetTileAt(topTile, rightTile) == 1) {
		mJumpForce = 0.0f;
	}
	if (mCurrentLevelMap->GetTileAt(topTile, leftTile) == 1) {
		mJumpForce = 0.0f;
	}

	//restrict Mario's X Position
	if (newXPos < 0.0f || newXPos + mTexture->GetWidth() > SCREEN_WIDTH) {
		newXPos = GetPosition().x;
	}

	//restrict Mario's Y Position
	if (newYPos < 0.0f || newYPos + mTexture->GetHeight() > SCREEN_HEIGHT) {
		newYPos = GetPosition().y;
		mJumpForce = 0.0f;
	}


	SetPosition(Vector2D(newXPos, newYPos));
	mDestRect->x = mPosition.x; 
	mDestRect->y = mPosition.y;

}

void CharacterMario::PollInput()
{
	mXVelocity = 0.0f;

	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_A]) {
		mFlipState = SDL_FLIP_HORIZONTAL;
		mXVelocity += -25.0f;
	}
	else if (state[SDL_SCANCODE_D]) {
		mFlipState = SDL_FLIP_NONE;
		mXVelocity += 25.0f;
	}

	if (state[SDL_SCANCODE_SPACE]) {
		if (mCanJump) {
			Jump();
		}

	}
}

