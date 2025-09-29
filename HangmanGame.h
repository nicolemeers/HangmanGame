#include <thread>
#include "AssetManager.h"
#include "Window.h"
#include "TextLetters.h"
#include "Text_Object.h"
#include "RendererEngine.h"
#include "Gallows_Object.h"
#include "GallowsMan.h"
#include "RenderObject.h"
#include "InputBox.h"
#pragma once

class HangmanGame
{
public:
	void init();

	// the main game loop
	bool mainLoop();
	
	// we need to have something create all of the objects
	// when they are created, they need to be registered with the rendererengine
		// and when the rendererengine unregisters, it'll delete and deallocate those objects
	// just make a function that will allocate the assets on its own thread, and then
	// this will loop and make all of the objects 
	// one for each letter, and then one for each of the letters in the hangman game
	// as well as one for each underscore

	// we will create the object and hand its pointer off to the rendererengine
	// the logic will also get its objects as needed

	//bool endGame();

	void close();
private:

	// will have some starting value
	// when zero, then the game is over
	int m_chances;
	int m_mouseInput;
	int m_gameState;
	std::string m_keyDownInput;

	float m_mouseX;
	float m_mouseY;

	bool m_quit;

	//std::string m_wordToGuess;
	
	Window* m_window = nullptr;
	RendererEngine* m_renderer = nullptr;
	AssetManager* m_assetManager = nullptr;
	//Wordbank* m_wordBank; --> Assetmanager handles this
	TextLetters* m_textMngr = nullptr;
	GallowsMan* m_gallows = nullptr;
	InputBox* m_inputBox = nullptr;

	void loadAllAssets();
	void loadAssets();
	void createRenderObjects();
	void createGallowsObjects();
	void createTextObjects();
	void createWordTextObjects();
	void createInputObjects();

	void getTexturesForObjects(RenderObject* curObj, std::string name);

	std::string getKeyInput(int keyVal);

	// after the guess is done, we need to update based on results back (maybe make private?)
	// setting things visible, etc...
	void update();

	void resetGame();

	void drawScreen();
};

// this might store the stuff for the gallows instead???

