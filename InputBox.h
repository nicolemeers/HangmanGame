#include "AssetManager.h"
#include "Text_Object.h"
#pragma once
class InputBox
{
public:

	void init(int screenWidth, int screenHeight);
	std::string getString();

	void updateInputField(std::string newInput, AssetManager* assetManager);
	void updateInputTexture(AssetManager* assetManager);

	void registerInputFieldObject(RenderObject* inputObj);
	void registerInputUnderscore(RenderObject* underscoreObj);
	void registerGuessObject(RenderObject* guessObj);

	void close();

private:
	std::string m_textString;
	std::string m_underscore;

	// says Input:
	RenderObject* m_inputField;
	// _
	RenderObject* m_underscoreObj;
	// this is for what the person enters onto the screen
	RenderObject* m_nextGuess;
};

