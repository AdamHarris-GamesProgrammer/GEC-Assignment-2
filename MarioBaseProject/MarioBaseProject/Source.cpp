#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>

#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

using namespace std;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

GameScreenManager* gameScreenManager; //declares a gameScreenManager pointer object
Uint32 mTicksCount;

bool InitSDL();
void CloseSDL();

bool Update();

void Render();


int main(int argc, char* args[]) {
	if (InitSDL()) { //if SDL initializes successfully
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL2); //loads level1 as the starting level
		
		bool quit = false;

		while (!quit) { 
			Render(); //renders the screen
			quit = Update(); //updates object positions etc
		}
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
		gWindow = SDL_CreateWindow("Mario Bros",
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

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED); //TODO label this

		if (gRenderer != NULL) { //if the renderer was setup correctly
			//initialize PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags)) { //IMG_Init returns the flag that has been setup correctly if there is no return value then there was a error
				cout << "SDL_Image could not initialize. Error: " << IMG_GetError(); //As we are dealing with the IMG library now we use IMG_GetError() instead of SDL_GetError()
				return false; //return false, exits the program
			}
		}
		else {
			cout << "Renderer could not initialize. Error: " << SDL_GetError();
			return false; //return false, exits the program
		}

		mTicksCount = SDL_GetTicks();

		return true; //return true, starts the game loop.
	}
}

void CloseSDL() //this function will destroy anything SDL based left in the memory such as the window and the Image framework
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL; //sets the memory address for gWindow to NULL (0) this means that the memory address is essentially deleted

	delete gameScreenManager; //clears up the screen manager class
	gameScreenManager = NULL; 

	//releases the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL; //setting it to NULL prevents the destructor from being called twice 


	IMG_Quit(); //unloads the IMG related libraries
	SDL_Quit(); //unloads the SDL related libraries
}

bool Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)); //delays the game 16ms, creating (roughly) 60fps game play

	//calculates delta time
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	SDL_Event eventHandler; //declares an event

	SDL_PollEvent(&eventHandler); //polls the event handler to see if any events have happened within the previous cycle

	switch (eventHandler.type) {
	case SDL_QUIT: //this event is activated by clicking the X button on the window
		return true; //causes the game loop to end
		break;
	case SDL_KEYDOWN:
		switch (eventHandler.key.keysym.sym) {
		case SDLK_ESCAPE: //if the player presses Esc then the game will quit
			return true;
			break;

		case SDLK_l: //checks to see if the l key has been released
			gameScreenManager->ChangeScreen(SCREEN_LEVEL1); //changes to the menu level
			break;
		case SDLK_2: //checks to see if the p key has been released
			gameScreenManager->ChangeScreen(SCREEN_LEVEL2); //changes to the first level
		}
	
	}

	gameScreenManager->Update(deltaTime, eventHandler); //updates whatever level is currently being displayed

	return false; //since the player has not quit then they want to continue playing therefore Update returns false
}

void Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF); //uses the RGBA color model //this sets the color of the screen to red
	SDL_RenderClear(gRenderer); //clears the current frame buffer with the current draw color

	gameScreenManager->Render(); //renders the current screen

	SDL_RenderPresent(gRenderer); //presents the current frame buffer so the user can see it
}

