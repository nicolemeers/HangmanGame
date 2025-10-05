#include "AssetManager.h"

struct SDLTextureDeleter {
	void operator()(SDL_Texture* texture) const {
		if (texture) {
			SDL_DestroyTexture(texture);
		}
	}
};


bool AssetManager::init()
{
	m_wordBank = new Wordbank();
	m_wordBank->Init();

	// Initialize SDL_ttf
	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! TTF_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		// specify the path to your font file and font size
		m_Font = TTF_OpenFont(M_MY_FONT, M_FONT_SIZE);

		if (!m_Font) {
			printf("Failed to load font: %s\n", SDL_GetError());
			return false;
		}
	}

	// the img libary is now automatically initalized and handled

	m_wordBank->PullWordsFromThesaurus();
	// cache locally and then read from that
}

void AssetManager::loadAssets(RendererEngine* renderer, std::vector<std::string>& assetLocation)
{
	for (int i = 0; i < assetLocation.size(); i++)
	{
		//m_surfaces[assetLocation[i]] = loadSurface(assetLocation[i]);
		m_surfaces.emplace(assetLocation[i], loadSurface(assetLocation[i]));
	}
	loadAllTextures(renderer);
}

void AssetManager::loadFontAssets(RendererEngine* renderer, std::vector<std::string>& assetLocation)
{

	for (int i = 0; i < assetLocation.size(); i++)
	{
		//m_surfaces[assetLocation[i]] = loadFontSurface(assetLocation[i]);
		m_surfaces.emplace(assetLocation[i], loadFontSurface(assetLocation[i]));
	}
	loadAllTextures(renderer);
}

std::shared_ptr<SDL_Texture> AssetManager::getTexture(const std::string& name)
{
	if (checkTexture(name))
		return m_textures[name];
	return nullptr;
}

void AssetManager::getDimensions(const std::string& name, int& w, int &h)
{
	if (checkTexture(name))
	{
		w = m_dimensions[name].first;
		h = m_dimensions[name].second;
	}
}

std::string AssetManager::getWordToGuess()
{
	std::string wordChosen = m_wordBank->GetWordToGuess();
	std::transform(wordChosen.begin(), wordChosen.end(), wordChosen.begin(), ::toupper);
	return wordChosen;
}

//void AssetManager::unloadTextures()
//{
//	// don't forget about this
//}

void AssetManager::close()
{
	// the surfaces are already freed
	// the textures are handled with smart pointers
	delete m_wordBank;
	m_wordBank = nullptr;

}

SDL_Surface* AssetManager::loadSurface(std::string convertToTexture)
{
	SDL_Surface* loadedSurface = IMG_Load(convertToTexture.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", convertToTexture.c_str(), SDL_GetError());
		return nullptr;
	}
	return loadedSurface;
}

SDL_Surface* AssetManager::loadFontSurface(std::string convertToTexture)
{
	// Create surface with rendered text
	const char* textToRender = convertToTexture.c_str();
	SDL_Surface* surfaceOfText = TTF_RenderText_Solid(m_Font, textToRender, 0, m_Color);

	if (!surfaceOfText) {
		printf("Failed to create text surface: %s\n", SDL_GetError());
		return nullptr;
	}

	return surfaceOfText;
}

void AssetManager::loadAllTextures(RendererEngine* renderer)
{
	//auto end = m_surfaces.end(); we will be deallocating the surface and changing the map - we will remove from map when done
	for (auto i = m_surfaces.begin(); i != m_surfaces.end(); i++)
	{
		//m_textures[i->first] = loadTexture(renderer, i->second, i->first);
		m_textures.emplace(i->first, loadTexture(renderer, i->second, i->first));
	}
}

std::shared_ptr<SDL_Texture> AssetManager::loadTexture(RendererEngine* renderer, SDL_Surface* surfaceToConvert, const std::string& name)
{
	if (!surfaceToConvert)
		return nullptr;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->getRenderer(), surfaceToConvert);

	if (!texture)
	{
		printf("Failed to create text texture: %s\n", SDL_GetError());
		return nullptr;
	}

	// set texture filtering to linear
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_LINEAR);

	// save the dimensions of the surface
	m_dimensions.emplace(name, std::pair<int, int>{surfaceToConvert->w, surfaceToConvert->h});
	
	// Get rid of old surface, now that we have the dimensions
	SDL_DestroySurface(surfaceToConvert);
	m_surfaces[name] = nullptr;

	// put in a custom deleter for deleting the textures
	return std::shared_ptr<SDL_Texture>(texture, SDLTextureDeleter{});
}

bool AssetManager::checkTexture(const std::string& name)
{
	if (m_textures.find(name) != m_textures.end())// && m_dimensions.find(name) != m_dimensions.end())
		return true;
	return false;
}


