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
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	SetPosition(startPosition);
	mCollisionRadius = mTexture->GetWidth()/2;
	mCurrentLevelMap = levelMap;
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

void Character::Jump()
{
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::MoveLeft(float deltaTime)
{
	mPosition.x -= MovementSpeed;
}

void Character::MoveRight(float deltaTime)
{
	mPosition.x += MovementSpeed;
}

void Character::Render(){}

void Character::Update(float deltaTime, SDL_Event eventHandler){
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

void Character::CancelJump()
{
	mJumpForce = 0;
}

float Character::GetCollisionRadius() {
	return mCollisionRadius;
}

