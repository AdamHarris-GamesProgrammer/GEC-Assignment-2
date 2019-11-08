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

	mRenderer = NULL; //sets the renderer to null
}

bool Texture2D::LoadFromFile(std::string filePath)
{
	Free(); //clears the memory of the current texture

	//load the image
	SDL_Surface* pSurface = IMG_Load(filePath.c_str()); //loads the image at the required file path
	if (pSurface != NULL) { //if the image loaded successfully
		/*
			SDL_SetColorKey(SDL_Surface, flag, key)
			The color key determines a color that is to be treated as a transparent pixel, a common example of this is magenta
			it takes 3 parameters
			SDL_Surface: the surface is the surface that you want to pass into the function
			Flag: the flag is the variable that determines whether the color key is activated
			Key: the key is the color value of the pixel that will be treated as a transparent pixel in this case we are using cyan
			
		*/
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xff, 0xff));
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface); //creates a texture pointer from an existing surface in this case pSurface
		mWidth = pSurface->w; //sets the texture width equal to the surface width
		mHeight = pSurface->h; //sets the texture height equal to the surface height

		if (mTexture == NULL) {
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl; //outputs the error associated with the SDL fault
		}
	}
	else {
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError() << std::endl; //outputs the error associated with the image fault
	}

	SDL_FreeSurface(pSurface); //removes the loaded surface from memory
	return mTexture != NULL; //returns if the texture exists if texture != NULL then it exists so the function returns true
}

void Texture2D::Free()
{
	if (mTexture != NULL) { //releases all memory associated with this class
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0; 
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle /*= 0.0f*/)
{
	SDL_Rect renderLocation = { 0,0, mWidth, mHeight }; //this holds the destination rect for the texture, this is where it will be rendered on the screen.

	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, SDL_FLIP_HORIZONTAL); //copies the texture from the position of the source rect on the sprite sheet to a rotation and position on the screen
}
