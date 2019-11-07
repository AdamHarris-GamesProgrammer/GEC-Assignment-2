#include "Texture2D.h"
#include <SDL_image.h>

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mTexture = NULL;

	int mWidth = 0;
	int mHeight = 0;
}

Texture2D::~Texture2D()
{
	Free();

	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(std::string filePath)
{
	Free(); //clears the memory of the current texture


	//load the image
	SDL_Surface* pSurface = IMG_Load(filePath.c_str());
	if (pSurface != NULL) {
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xff, 0xff));
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		mWidth = pSurface->w;
		mHeight = pSurface->h;

		if (mTexture == NULL) {
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl;
		}
	}
	else {
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError() << std::endl;
	}


	SDL_FreeSurface(pSurface); //removes the loaded surface from memory
	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle /*= 0.0f*/)
{
	SDL_Rect renderLocation = { 0,0, mWidth, mHeight }; //rect is a struct

	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, SDL_FLIP_HORIZONTAL);

	
}
