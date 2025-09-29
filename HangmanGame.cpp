#include "HangmanGame.h"

enum winlossState
{
	IN_PLAY,
	WIN,
	LOSE
};

void HangmanGame::init()
{
	// our chances
	m_chances = 11;
	// no mouse input
	m_mouseInput = false;
	// current game state
	m_gameState = IN_PLAY;

	// allocate
	m_window = new Window();
	m_renderer = new RendererEngine();
	m_assetManager = new AssetManager();
	m_textMngr = new TextLetters();
	m_gallows = new GallowsMan();
	m_inputBox = new InputBox();

	// this needs a thread in it --> just call a thread for this initalization
	std::thread threadForWordbank(&AssetManager::init, m_assetManager);

	m_window->init();
	m_renderer->init(m_window->getRenderer());

	loadAssets();
	
	// we need this word before we can do anything else with the objects for text, unfortunately
	threadForWordbank.join();
	m_textMngr->setWordToGuess(m_assetManager->getWordToGuess());
	
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

					if (m_gameState != IN_PLAY)
					{
						if (m_window->getKeyDownType() == keydown::MOUSEDOWN)
						{
							m_window->getMouseCoors(m_mouseX, m_mouseY);
							m_mouseInput = true;
						}
						//else
							//m_mouseInput = false;
						continue;
					}
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
						m_mouseInput = false;
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
		if (m_quit)
			quit = true;

		// we need to draw the screen
		drawScreen();

	}

	
	return false;
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
		else if (i == "Game Over") { m_gallows->registerGameEndText(textObj, i); }
		else if (i == "Game Win") { m_gallows->registerGameEndText(textObj, i); }
		else if (i == "New Game") { continue; }
		else if (i == "Exit Game") { continue; }
		else
			m_textMngr->registerLetters(textObj, i);

		getTexturesForObjects(textObj, i);
	}

	createWordTextObjects();
	createInputObjects();
}

void HangmanGame::createWordTextObjects()
{
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
}

void HangmanGame::createInputObjects()
{
	Text_Object* textObj = new Text_Object();
	Text_Object* textObj2 = new Text_Object();
	Text_Object* newGameTextObj = new Text_Object();
	Text_Object* exitGameTextObj = new Text_Object();
	Text_Object* underscoreTextObj = new Text_Object();

	textObj->setName("Input:");
	newGameTextObj->setName("New Game");
	exitGameTextObj->setName("Exit Game");
	underscoreTextObj->setName("_");	

	textObj->setVisibleFlag();
	textObj2->setVisibleFlag();
	underscoreTextObj->setVisibleFlag();

	m_renderer->registerObj(textObj);
	m_renderer->registerObj(textObj2);
	m_renderer->registerObj(newGameTextObj);
	m_renderer->registerObj(exitGameTextObj);
	m_renderer->registerObj(underscoreTextObj);

	m_inputBox->registerInputFieldObject(textObj);
	m_inputBox->registerGuessObject(textObj2);
	m_inputBox->registerNewGameObject(newGameTextObj);
	m_inputBox->registerEndGameObject(exitGameTextObj);
	m_inputBox->registerInputUnderscore(underscoreTextObj);

	getTexturesForObjects(textObj, "Input:");
	getTexturesForObjects(newGameTextObj, "New Game");
	getTexturesForObjects(exitGameTextObj, "Exit Game");
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

	if (m_gameState != IN_PLAY)
	{
		// we need to chieck if the mouse was clicked and in the right spot
		if (m_mouseInput)
		{
			if (m_inputBox->checkifExitGameClicked(m_mouseX, m_mouseY))
				m_quit = true;
			if (m_inputBox->checkIfNewGameClicked(m_mouseX, m_mouseY))
			{
				resetGame();
			}
		}
	}
	else
	{
		if (m_chances == 0)
		{
			m_gameState = LOSE;
			m_textMngr->showFullWord();
			m_gallows->updateGallows();
			m_inputBox->showNewGameBox();
		}
		if (m_textMngr->checkIfWordIsComplete())
		{
			m_gallows->setWinState();
			m_inputBox->showNewGameBox();
			m_gameState = WIN;
		}
	}

	// we need to check if the chances are zero
	// 
	// we need to check if the word is full
}

void HangmanGame::resetGame()
{
	m_chances = 11;
	m_mouseInput = false;
	m_gameState = IN_PLAY;
	m_quit = false;

	// reset input and end game text
	m_inputBox->resetInputBox();
	// reset handman
	m_gallows->resetState();
	// reset guessed letters, word to guess, and "blank" spaces
	m_textMngr->reset(m_renderer);
	m_textMngr->setWordToGuess(m_assetManager->getWordToGuess());
	// the objects needed for the word to guess and its blank spaces
	createWordTextObjects();
	m_textMngr->resetWordToGuess(m_window->getScreenWidth(), m_window->getScreenHeight());
}

void HangmanGame::drawScreen()
{
	m_renderer->clearScreen();
	m_renderer->drawObjects(1);

	m_renderer->renderPresent();
}
