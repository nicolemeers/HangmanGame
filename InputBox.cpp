#include "InputBox.h"

void InputBox::init(int screenWidth, int screenHeight)
{	
	m_inputField->setX(25);
	m_inputField->setY(screenHeight - 400);
	m_underscoreObj->setX(300 + m_inputField->getTextureWidth());
	m_underscoreObj->setY(screenHeight + m_inputField->getTextureHeight());
	
	m_nextGuess->setX(25 + m_inputField->getTextureWidth());
	m_nextGuess->setY(screenHeight - 400);

	m_newGame->setX(850);
	m_newGame->setY(800);

	m_exitGame->setX(850);
	m_exitGame->setY(950);
}

void InputBox::updateInputField(std::string& newInput, AssetManager* assetManager)
{
	m_textString = newInput;
	updateInputTexture(assetManager);
	m_nextGuess->setVisibleFlag();
}

void InputBox::updateInputTexture(AssetManager* assetManager)
{
	if (m_textString != "") // the size of the string is not zero
	{
		m_nextGuess->setTexture(assetManager->getTexture(m_textString));
		m_nextGuess->setName(m_textString);
	}
	else
		m_nextGuess->setTextureDimensions(0, 0);
}

void InputBox::showNewGameBox()
{
	m_newGame->setVisibleFlag();
	m_exitGame->setVisibleFlag();
}

bool InputBox::checkifExitGameClicked(int x, int y)
{
	if (x >= 850 && x <= (850 + m_newGame->getTextureWidth()))
		if (y >= 950 && y <= (950 + m_newGame->getTextureHeight()))
			return true;
	return false;
}

bool InputBox::checkIfNewGameClicked(int x, int y)
{
	if (x >= 850 && x <= (850 + m_newGame->getTextureWidth()))
		if (y >= 800 && y <= (800 + m_newGame->getTextureHeight()))
			return true;
	return false;
}

void InputBox::registerInputFieldObject(RenderObject* inputObj)
{
	m_inputField = inputObj;
}

void InputBox::registerInputUnderscore(RenderObject* underscoreObj)
{
	m_underscoreObj = underscoreObj;
}

void InputBox::registerGuessObject(RenderObject* guessObj)
{
	m_nextGuess = guessObj;
}

void InputBox::registerNewGameObject(RenderObject* newGameObj)
{
	m_newGame = newGameObj;
}

void InputBox::registerEndGameObject(RenderObject* endGameObj)
{
	m_exitGame = endGameObj;
}

void InputBox::resetInputBox()
{
	m_newGame->unsetVisibleFlag();
	m_exitGame->unsetVisibleFlag();
}

void InputBox::close()
{
	// need to deallocate all of the objects
	// no, it's registered with the rendererengine, that will delete them all when it unregisters
}
