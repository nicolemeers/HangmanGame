#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "RendererEngine.h"
#include "RenderObject.h"
#include "Wordbank.h"
#pragma once

// AKA RESOURCE MANAGER
class AssetManager 
{
public:
	bool init();
	// will allocate all of the assets
	void loadAssets(RendererEngine* renderer, std::vector<std::string>& assetLocation);

	void loadFontAssets(RendererEngine* renderer, std::vector<std::string>& assetLocation);

	// the function anything needs to call in order to get its texture
	std::shared_ptr<SDL_Texture> getTexture(std::string name);
	void getDimensions(std::string name, int& w, int &h);
	std::string getWordToGuess();

	//void unloadTextures(); // maybe have this private and do in close -> using smart pointers

	void close();

private:
	Wordbank* m_wordBank;
	// For the font textures
	TTF_Font* m_Font = NULL;
	const char* M_MY_FONT = "C:/Windows/Fonts/BELLI.ttf";
	int M_FONT_SIZE = 140;
	int M_GAMEOVER_FONT_SIZE = 320;
	// Black color for text
	SDL_Color m_Color = { 0x00, 0x00, 0x00, 0xFF };

	// use a map to keep track of the names
	std::unordered_map<std::string, SDL_Surface*> m_surfaces;
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_textures;
	std::unordered_map<std::string, std::pair<int, int>> m_dimensions;

	SDL_Surface* loadSurface(std::string convertToTexture);
	SDL_Surface* loadFontSurface(std::string convertToTexture);
	// will unload the surface once the texture is created
	void loadAllTextures(RendererEngine* renderer);
	std::shared_ptr<SDL_Texture> loadTexture(RendererEngine* renderer, SDL_Surface* surfaceToConvert, std::string name);

	bool checkTexture(std::string name);

	

	// will track the reference counter
	// we will use smart pointers so we don't need to explicity reference count
};

