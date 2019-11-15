#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h" //keeps the promise of the forward declaration
#include "Character.h"
#include "CharacterMario.h"
#include "Collisions.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();

	mLevelMap = NULL;
}

GameScreenLevel1::~GameScreenLevel1() {
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete marioCharacter;
	marioCharacter = NULL;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event event) {
	if (mScreenShake) {
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		if (mScreenShakeTime <= 0.0f) {
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}
	marioCharacter->Update(deltaTime, event);
	luigiCharacter->Update(deltaTime, event);

	if (Collisions::Instance()->Circle(marioCharacter->GetCollisionCircle(), luigiCharacter->GetCollisionCircle())) {
		
	}

	UpdatePowBlock();

}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), marioCharacter->GetCollisionBox())) {
		std::cout << "BOOP" << std::endl;
		if (mPowBlock->IsAvailable()) {
			std::cout << "Available" << std::endl;
			if (marioCharacter->IsJumping()) {
				std::cout << "character is jumping" << std::endl;
				DoScreenShake();
				mPowBlock->TakeAHit();
				marioCharacter->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::Render() {
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE); //renders the background texture onto the screen 
	marioCharacter->Render();
	luigiCharacter->Render();
	mPowBlock->Render();
}

bool GameScreenLevel1::SetUpLevel() {
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	SetLevelMap();
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	marioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	luigiCharacter = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(128, 330), mLevelMap);
	mBackgroundTexture = new Texture2D(mRenderer); //creates a new texture
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) { //if it fails to load the texture
		std::cout << "Failed to load background texture!"; //output failed
		return false;
	}
	else {

		return true;
	}
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	if (mLevelMap != NULL) {
		delete mLevelMap;
	}

	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}
