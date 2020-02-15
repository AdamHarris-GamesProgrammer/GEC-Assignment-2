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
	PollInput(eventHandler);

	float newXPos = GetPosition().x;
	float newYPos = GetPosition().y;


	if (mJumping) {
		mCanJump = false;
		std::cout << "Jumping" << std::endl;
		//adjusts position
		newYPos -= mJumpForce * deltaTime;

		//reduces jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f) {
			mJumping = false;
		}
	}

	if (mXVelocity != 0.0f) {
		std::cout << "mXVelocity: " << mXVelocity << std::endl;
		newXPos += mXVelocity * mMovementSpeed * deltaTime;
	}


	int leftTile = newXPos / TILE_WIDTH;
	int rightTile = (newXPos + mTexture->GetWidth()) / TILE_WIDTH;
	int topTile = newYPos / TILE_HEIGHT;
	int bottomTile = (newYPos + mTexture->GetHeight()) / TILE_HEIGHT;


	//left collision
	if (mCurrentLevelMap->GetTileAt(bottomTile -1, leftTile) == 1) {
		newXPos = GetPosition().x;
	}

	//right collision
	if (mCurrentLevelMap->GetTileAt(bottomTile-1, rightTile) == 1) {
		newXPos = GetPosition().x;
	}

	//foot collision
	if (mCurrentLevelMap->GetTileAt(bottomTile, rightTile) == 1 || mCurrentLevelMap->GetTileAt(bottomTile, leftTile) == 1) {
		mCanJump = true;
	}
	else {
		newYPos += GRAVITY * deltaTime;
	}

	//head collision
	if (mCurrentLevelMap->GetTileAt(topTile, rightTile) == 1) {
		mJumpForce = 0.0f;
	}

	SetPosition(Vector2D(newXPos, newYPos));

}

void CharacterMario::PollInput(SDL_Event eventHandler)
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

