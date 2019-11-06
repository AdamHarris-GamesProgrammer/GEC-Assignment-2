#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>

#include "Constants.h"

using namespace std;

SDL_Window* gWindow = NULL;

bool InitSDL();
void CloseSDL();

int main(int argc, char* args[]) {
	if (InitSDL()) { //if SDL initializes successfully
		//then...
		SDL_Delay(5000); //wait for 5 seconds, this will be replaced with a game loop
	}

	CloseSDL(); //once the delay is over then SDL will close destroying memory that is being used up

	return 0;
}

bool InitSDL() //this function initializes SDL and creates the window with the predetermined sizes from the Constants.h file
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //Initializes the Video framework in SDL, this method returns a bool allowing us to see if it successfully initializes
		cout << "SDL did not initialize. Error: " << SDL_GetError(); //if it fails, then print out the error code
		return false; //returns false, exits the program
	}
	else {
		//if execution did not fail then it creates a window 

		/*
			SDL_CreateWindow takes 6 parameters,
			param title: This is the string that will be displayed at the top of the window
			param x: This is the x position on the screen that the window will open at, as we are not defining a position we use SDL_WINDOWPOS_UNDEFINED this flag means that it will create the window in the middle of the X axis
			param y: This is the same as param x
			param w: This is the width of the window
			param h: This is the height of the window
			param flag: This allows us to select custom flags for the window in this case we use SDL_WINDOW_SHOW, this means that the window will automatically open and be in focus
		*/ 
		gWindow = SDL_CreateWindow("Mario Bros - Assignment 2",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//if the window has failed to be created
		if (gWindow == NULL) {
			//then...
			cout << "Window was not created. Error: " << SDL_GetError(); //output the error code
			return false; //return false, exits the program
		}

		return true; //return true, starts the game loop.
	}
}

void CloseSDL() //this function will destroy anything SDL based left in the memory such as the window and the Image framework
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL; //sets the memory address for gWindow to NULL (0) this means that the memory address is essentially deleted

	IMG_Quit(); //unloads the IMG related libraries
	SDL_Quit(); //unloads the SDL related libraries
}
