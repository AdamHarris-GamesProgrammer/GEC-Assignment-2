#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h" //keeps the promise of the forward declaration
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
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

	mEnemies.clear();
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

	UpdatePowBlock();
	UpdateEnemies(deltaTime, event);

}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), marioCharacter->GetCollisionBox())) {
		if (mPowBlock->IsAvailable()) {
			if (marioCharacter->IsJumping()) {
				DoScreenShake();
				mPowBlock->TakeAHit();
				marioCharacter->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event event)
{
	if (!mEnemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++) {

			if (mEnemies[i]->GetPosition().y > 300.0f) {

				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) ||
					mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f)) 
				{
					mEnemies[i]->SetAlive(false);
				}
			}

			mEnemies[i]->Update(deltaTime, event);

			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && 
				(mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)) {
				//ignore collision if the enemy is behind a pipe
			}
			else {
				if (Collisions::Instance()->Circle(mEnemies[i], marioCharacter)) {
					std::cout << "Mario is dead" << std::endl;
					marioCharacter->SetState(CHARACTER_STATE::DEAD);
				}
				
			}

			if (!mEnemies[i]->GetAlive()) {
				enemyIndexToDelete = i;
			}

			if (enemyIndexToDelete != -1) {
				std::cout << "Enemy is deleted" << std::endl;
				mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
			}

		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, speed);
	mEnemies.push_back(koopaCharacter);

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		std::cout << mEnemies[i] << std::endl;

	}
	std::cout << std::endl;
}

void GameScreenLevel1::Render() {
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE); //renders the background texture onto the screen 
	marioCharacter->Render();
	mPowBlock->Render();

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}

}

bool GameScreenLevel1::SetUpLevel() {
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	SetLevelMap();




	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	marioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	mBackgroundTexture = new Texture2D(mRenderer); //creates a new texture

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

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

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->TakeDamage();
	}
}
