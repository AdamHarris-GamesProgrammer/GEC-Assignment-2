#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : TiledLevel(renderer)
{
	LoadMap("Maps/Level2.csv");
}

void GameScreenLevel2::Render()
{
	TiledLevel::Render();


}

void GameScreenLevel2::Update(float deltaTime, SDL_Event event)
{

}
