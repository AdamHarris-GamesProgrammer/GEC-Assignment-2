#include "Character.h"
#include "CharacterMario.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Commons.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : Character(renderer, imagePath, startPosition)
{
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	SetPosition(startPosition);
}

void CharacterMario::Render() 
{
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(GetPosition(), SDL_FLIP_NONE, 0);
	}
	else {
		mTexture->Render(GetPosition(), SDL_FLIP_HORIZONTAL, 0);
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event eventHandler)
{
	if (mJumping) {
		//adjusts position
		mPosition.y -= mJumpForce * deltaTime;

		//reduces jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f) {
			mJumping = false;
		}
	}

	switch (eventHandler.type)
	{
	case SDL_KEYDOWN:
		switch (eventHandler.key.keysym.sym) {
		case SDLK_a:
			mFacingDirection = FACING_LEFT;
			MoveLeft(deltaTime);
			break;
		case SDLK_d:
			mFacingDirection = FACING_RIGHT;
			MoveRight(deltaTime);
			break;
		case SDLK_SPACE:
			Jump();
			break;
		}
	}
	if (mPosition.y <= 372) {
		AddGravity(deltaTime);
	}
}


