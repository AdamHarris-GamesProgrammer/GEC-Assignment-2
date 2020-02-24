#pragma once
#include "TiledLevel.h"
#include "Texture2D.h" //keeps the promise of the forward declaration
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "LevelMap.h"

class GameScreenLevel2 : public TiledLevel
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);


	void Render() override;
	void Update(float deltaTime, SDL_Event event) override;
private:
	CharacterMario* mPlayer;

	void SetLevelMap();

	LevelMap* mLevelMap;
};

