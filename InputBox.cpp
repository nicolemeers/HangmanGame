#include "InputBox.h"

void InputBox::init(int screenWidth, int screenHeight)
{
	m_textString = "";
	m_underscore = "_";
	
	m_inputField->setX(25);
	m_inputField->setY(screenHeight - 400);
	m_underscoreObj->setX(300 + m_inputField->getTextureWidth());
	m_underscoreObj->setY(screenHeight + m_inputField->getTextureHeight());
	
	m_nextGuess->setX(25 + m_inputField->getTextureWidth());
	m_nextGuess->setY(screenHeight - 400);
}

std::string InputBox::getString()
{
	return m_textString;
}

void InputBox::updateInputField(std::string newInput, AssetManager* assetManager)
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

void InputBox::close()
{
	// need to deallocate all of the objects
	// no, it's registered with the rendererengine, that will delete them all when it unregisters
}
