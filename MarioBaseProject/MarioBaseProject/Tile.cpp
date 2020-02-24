#include "Tile.h"

Tile::Tile(SDL_Renderer* renderer, SDL_Rect* src, SDL_Rect* dest, int tileType)
{
	mSrcRect = src;
	mDestRect = dest;

	position.x = dest->x;
	position.y = dest->y;
	
	mDestRect = dest;

	mTileType = tileType;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile("Images/TileMap.png");
}

Tile::~Tile()
{

}

void Tile::Render(SDL_Renderer* renderer)
{
	if (mTexture) {
		mTexture->Render(mSrcRect, mDestRect, SDL_FLIP_NONE, 0.0f);
	}
}

void Tile::Update(float deltaTime)
{

}
