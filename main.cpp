#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "HangmanGame.h"
#pragma once

int main(int argc, char* args[])
{

	HangmanGame hangmanGame;

	hangmanGame.init();

	while (hangmanGame.mainLoop()) {}

	hangmanGame.close();



	return 0;
}


// we need the word bank
// the word bank needs a parser
// the word bank also needs to do the curl stuff

/*
* this didn't like being in a class
// Use libcurl to pull data from the API
// function to pass into libcurl handlers (it is used whenever there is data that needs to be saved)
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData);

*/