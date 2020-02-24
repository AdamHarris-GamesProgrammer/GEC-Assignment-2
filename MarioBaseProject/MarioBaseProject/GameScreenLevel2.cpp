#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : TiledLevel(renderer)
{
	LoadMap("Maps/Level2.csv");

	SetLevelMap();
	mPlayer = new CharacterMario(renderer, "Images/Mario.png", Vector2D(32, SCREEN_HEIGHT - 32 - 32), mLevelMap);
}

void GameScreenLevel2::Render()
{
	TiledLevel::Render();

	mPlayer->Render();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event event)
{
	mPlayer->Update(deltaTime, event);
}

void GameScreenLevel2::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{3,0,0,0,3,0,0,0,0,0,0,3,0,0,0,3},
		{0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0},
		{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	if (mLevelMap != NULL) {
		delete mLevelMap;
	}

	mLevelMap = new LevelMap(map);

	for (unsigned int row = 0; row < GetLevelHeight(); row++) {
		for (unsigned int column = 0; column < GetLevelWidth(); column++) {
			std::cout << mMap[row][column];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "map" << std::endl;
	for (unsigned int row = 0; row < GetLevelHeight(); row++) {
		for (unsigned int column = 0; column < GetLevelWidth(); column++) {
			std::cout << map[row][column];
		}
		std::cout << std::endl;
	}
}
