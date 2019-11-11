#include "Character.h"
#include "Texture2D.h"



Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	SetPosition(startPosition);
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= 1;
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += 1;
}

void Character::Render()
{
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(GetPosition(), SDL_FLIP_NONE, 0);
	}
	else {
		mTexture->Render(GetPosition(), SDL_FLIP_HORIZONTAL, 0);
	}

}

void Character::Update(float deltaTime, SDL_Event eventHandler)
{

	
	switch (eventHandler.type)
	{
		case SDL_KEYDOWN:
			switch (eventHandler.key.keysym.sym) {
				case SDLK_a:
					MoveLeft(deltaTime);
					break;
				case SDLK_d:
					MoveRight(deltaTime);
					break;
			}
	}
	



	
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition.x = newPosition.x;
	mPosition.y = newPosition.y;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

