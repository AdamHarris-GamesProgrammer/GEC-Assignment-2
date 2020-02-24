#pragma once

#include "TileInformation.h"
#include "Texture2D.h"

class Tile
{
public:
	Tile(SDL_Renderer* renderer, SDL_Rect* src, SDL_Rect* dest, int tileType);
	~Tile();

	void Render(SDL_Renderer* renderer);

	void Update(float deltaTime);

	int GetTileType() const { return mTileType; }
	
private:
	int mTileType;

	Vector2D position;

	Texture2D* mTexture;

	SDL_Rect* mSrcRect;
	SDL_Rect* mDestRect;
};

