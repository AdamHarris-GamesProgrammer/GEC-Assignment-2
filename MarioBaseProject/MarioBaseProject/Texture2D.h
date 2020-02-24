#pragma once

#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include "SDL.h"
#include "Commons.h"
#include <string>
#include <iostream>

class Texture2D {
public:
	Texture2D(SDL_Renderer* renderer); //constructor, sets the value of mRenderer.
	~Texture2D(); //destructor, clears up memory associated with the Texture

	bool LoadFromFile(std::string filePath); //loads the texture from a file
	void Free(); //frees the memory associated with the texture
	
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f); //renders the texture, with a; position, flip status and a rotation 
	void Render(SDL_Rect* srcRect, SDL_Rect* destRect, SDL_RendererFlip flip, double angle = 0.0f);

	//returns width and height
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; } 
private:
	SDL_Renderer* mRenderer; //this is the renderer that has been passed into the constructor
	SDL_Texture* mTexture; //contains the texture

	//width and height of the texture
	int mWidth;
	int mHeight; 
};



#endif //_TEXTURE2D_H