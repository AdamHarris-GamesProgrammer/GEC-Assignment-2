#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h" //keeps the promise of the forward declaration
#include "Character.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1() {
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete myCharacter;
	myCharacter = NULL;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event event) {
	myCharacter->Update(deltaTime, event);
}

void GameScreenLevel1::Render() {
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE); //renders the background texture onto the screen 
	myCharacter->Render();
}

bool GameScreenLevel1::SetUpLevel() {
	myCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));

	mBackgroundTexture = new Texture2D(mRenderer); //creates a new texture
	if (!mBackgroundTexture->LoadFromFile("Images/Test.bmp")) { //if it fails to load the texture
		std::cout << "Failed to load background texture!"; //output failed
		return false;
	}
	else {
		return true;
	}
}