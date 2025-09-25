#include "HangmanGame.h"

void HangmanGame::init()
{
	// our chances
	m_chances = 11;

	// allocate
	m_window = new Window();
	m_renderer = new RendererEngine();
	m_assetManager = new AssetManager();
	m_textMngr = new TextLetters();
	m_gallows = new GallowsMan();
	m_inputBox = new InputBox();


	// this needs a thread in it --> just call a thread for this initalization
	std::thread threadForWordbank(&AssetManager::init, m_assetManager);
	//m_assetManager->init();

	m_window->init();
	m_renderer->init(m_window->getRenderer());

	// put this on a seperate thread
	//std::thread t_loadAssets(&HangmanGame::loadAssets, this);
	loadAssets();
	
	// we need this word before we can do anything else with the objects for text, unfortunately
	// so we can pull a base word, and then let the rest load (for another playthrough)
	threadForWordbank.join();
	m_textMngr->setWordToGuess(m_assetManager->getWordToGuess());
	
	// we need to make sure the assets are all loaded first
	//t_loadAssets.join();
	// we also need the textures when creating the objects
	createRenderObjects();

	int screenHeight = m_window->getScreenHeight();
	int screenWidth = m_window->getScreenWidth();

	m_textMngr->init(screenWidth, screenHeight);
	m_gallows->init(screenWidth, screenHeight);
	m_inputBox->init(screenWidth, screenHeight);
}

bool HangmanGame::mainLoop()
{
	bool quit = false;

	while (!quit)
	{
		// we need our event loop
		while (m_window->checkPollEvents())
		{
			//User requests quit
			if (m_window->isPollEventQuit())
			{
				quit = true;
			}
			else
			{
				if (m_window->isKeydownEventTrue())
				{
					// we will only display one letter
					// we will enter the guess once enter is hit
					// if backspace it will erase
					// if there is another key that has been input, you need to erase first
					if (m_window->getKeyDownType() == keydown::ENTER)
					{
						// now we can update the guesses letter
						if (m_keyDownInput != "")
						{
							bool valid = m_textMngr->checkGuess(m_keyDownInput);
							if (!valid)
							{
								m_chances--;
								m_gallows->updateGallows();
								
							}
							m_keyDownInput = "";
						}
					}
					else if (m_window->getKeyDownType() == keydown::BACKSPACE)
					{
						m_keyDownInput = "";
					}
					else
					{
						// whatever letter is here will be passed to the inputbox
						// the input box will update and get the appropriate texture
						// for the input character object it has
						if (m_keyDownInput == "")
							m_keyDownInput = getKeyInput(m_window->getKeyDownType());
					}
				}
				// handle keyboard inputs
				// need to update the keyboard inputs in the window class
			}
		}
		// somewhere around here, we need to update
		// we would be updating based solely on user input
		
		// WE NEED TO UPDATE
		update();

		// we need to draw the screen
		drawScreen();
	}

	
	return false;
}

void HangmanGame::takeInGuess(std::string guess)
{
	if (guess != "")
		m_textMngr->checkGuess(guess);
}

void HangmanGame::endGame()
{
	// when m_chances = 0, exit the loop,
	// call this
	// game over and go out of the loop
}

void HangmanGame::close()
{
	m_gallows->close();
	m_textMngr->close();
	m_renderer->close();
	m_assetManager->close();
	m_window->close();

	delete m_gallows;
	m_gallows = nullptr;

	delete m_textMngr;
	m_textMngr = nullptr;

	delete m_renderer;
	m_renderer = nullptr;

	delete m_assetManager;
	m_assetManager = nullptr;

	delete m_window;
	m_window = nullptr;
}

void HangmanGame::loadAllAssets()
{
	loadAssets();
}

void HangmanGame::loadAssets()
{
	m_assetManager->loadAssets(m_renderer, m_gallows->getImagesToDraw());
	m_assetManager->loadFontAssets(m_renderer, m_textMngr->getPossibleCharacters());
}

void HangmanGame::createRenderObjects()
{
	createGallowsObjects();
	createTextObjects();
}

void HangmanGame::createGallowsObjects()
{
	// the gallows and the textmng will have some kind of container for each and every render object
	for (std::string i : m_gallows->getImagesToDraw())
	{
		Gallows_Object* gallowsObj = new Gallows_Object();
		gallowsObj->setName(i);
		// we need to register this object with the renderer as well
			// the renderer could easily use a vector to store all of these
		m_renderer->registerObj(gallowsObj);
		m_gallows->registerToMap(gallowsObj, i);

		// we will set the texture for the object - each has to go through the asset manager 
		getTexturesForObjects(gallowsObj, i);
	}
}

void HangmanGame::createTextObjects()
{
	for (std::string i : m_textMngr->getPossibleCharacters())
	{
		Text_Object* textObj = new Text_Object();
		textObj->setName(i);
		
		m_renderer->registerObj(textObj);

		if (i == "Guessed Letters:")
		{
			textObj->setVisibleFlag();
			m_textMngr->registerGuessedLabel(textObj);
		}
		else if (i == "Input:") { continue; }
		else
			m_textMngr->registerLetters(textObj, i);

		getTexturesForObjects(textObj, i);
	}

	for (char c : m_textMngr->getWord())
	{
		Text_Object* textObj = new Text_Object();
		Text_Object* underscoreTextObj = new Text_Object();

		textObj->setName(std::string(1, c));
		underscoreTextObj->setName("_");

		m_renderer->registerObj(textObj);
		m_renderer->registerObj(underscoreTextObj);

		m_textMngr->registerWord(textObj);
		m_textMngr->registerUnderscore(underscoreTextObj);

		getTexturesForObjects(textObj, std::string(1, c));
		getTexturesForObjects(underscoreTextObj, "_");

		underscoreTextObj->setVisibleFlag();
	}
	createInputObjects();
}

void HangmanGame::createInputObjects()
{
	Text_Object* textObj = new Text_Object();
	Text_Object* textObj2 = new Text_Object();
	Text_Object* underscoreTextObj = new Text_Object();

	textObj->setName("Input:");
	underscoreTextObj->setName("_");

	textObj->setVisibleFlag();
	textObj2->setVisibleFlag();
	underscoreTextObj->setVisibleFlag();

	m_renderer->registerObj(textObj);
	m_renderer->registerObj(textObj2);
	m_renderer->registerObj(underscoreTextObj);

	m_inputBox->registerInputFieldObject(textObj);
	m_inputBox->registerGuessObject(textObj2);
	m_inputBox->registerInputUnderscore(underscoreTextObj);

	getTexturesForObjects(textObj, "Input:");
	getTexturesForObjects(underscoreTextObj, "_");

}

void HangmanGame::getTexturesForObjects(RenderObject* curObj, std::string name)
{
	curObj->setTexture(m_assetManager->getTexture(name));
	int w, h;
	m_assetManager->getDimensions(name, w, h);
	curObj->setTextureDimensions(w, h);
}

std::string HangmanGame::getKeyInput(int keyVal)
{
	switch (keyVal)
	{
	case keydown::Q:
		return "Q";
	case keydown::W:
		return "W";
	case keydown::E:
		return "E";
	case keydown::R:
		return "R";
	case keydown::T:
		return "T";
	case keydown::Y:
		return "Y";
	case keydown::U:
		return "U";
	case keydown::I:
		return "I";
	case keydown::O:
		return "O";
	case keydown::P:
		return "P";
	case keydown::A:
		return "A";
	case keydown::S:
		return "S";
	case keydown::D:
		return "D";
	case keydown::F:
		return "F";
	case keydown::G:
		return "G";
	case keydown::H:
		return "H";
	case keydown::J:
		return "J";
	case keydown::K:
		return "K";
	case keydown::L:
		return "L";
	case keydown::Z:
		return "Z";
	case keydown::X:
		return "X";
	case keydown::C:
		return "C";
	case keydown::V:
		return "V";
	case keydown::B:
		return "B";
	case keydown::N:
		return "N";
	case keydown::M:
		return "M";
	}
	//return std::string();
	return "";
}

void HangmanGame::update()
{
	// we need to update:
	// the gallows
	// the text
	// the input

	//m_gallows->updateGallows(); --> we only call this if a guess is wrong
	m_textMngr->update();
	m_inputBox->updateInputField(m_keyDownInput, m_assetManager);
}

void HangmanGame::drawScreen()
{
	m_renderer->clearScreen();
	m_renderer->drawObjects(1);

	m_renderer->renderPresent();
}
