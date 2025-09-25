#include <stdio.h>
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include "keydown_namespace.h"
#pragma once
class Window
{
public:
	//void drawGrid(Grid* mainGrid);
	//void drawBox(BasicBlock* baseBlock); // may do with grid directly instead

	Window();
	~Window();

	// start the window
	bool init();

	//Frees media and shuts down SDL
	void close();

	// get dimensions
	int getScreenHeight();
	int getScreenWidth();

	// get renderer and window
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

	// handle the sdl events
	bool checkPollEvents();
	bool isPollEventQuit() const;
	bool isKeydownEventTrue() const;
	// get the keydown event and return what key it is
	int getKeyDownType() const;

private:
	int m_screenHeight = 0;
	int m_screenWidth = 0;

	//The window we'll be rendering to
	SDL_Window* m_Window = NULL;
	//The window renderer (to draw on the window)
	SDL_Renderer* m_Renderer = NULL;
	// Event handler
	SDL_Event e;


};




