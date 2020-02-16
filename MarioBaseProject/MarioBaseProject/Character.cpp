#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"


Character::Character()
{
}

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* levelMap)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mFlipState = SDL_FLIP_NONE;
	SetPosition(startPosition);
	mCollisionRadius = mTexture->GetWidth()/2;
	mCurrentLevelMap = levelMap;

	mDestRect = new SDL_Rect();
	mDestRect->x = startPosition.x;
	mDestRect->y = startPosition.y;
	mDestRect->w = mTexture->GetWidth();
	mDestRect->h = mTexture->GetHeight();
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Jump()
{
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::Render(){
	mTexture->Render(mPosition, mFlipState);
}

void Character::Update(float deltaTime, SDL_Event eventHandler){
}

void Character::CancelJump()
{
	mJumpForce = 0;
}

