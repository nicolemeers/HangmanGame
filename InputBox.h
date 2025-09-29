#include "AssetManager.h"
#include "Text_Object.h"
#pragma once
class InputBox
{
public:

	void init(int screenWidth, int screenHeight);

	void updateInputField(std::string newInput, AssetManager* assetManager);
	void updateInputTexture(AssetManager* assetManager);
	void showNewGameBox();
	bool checkifExitGameClicked(int x, int y);
	bool checkIfNewGameClicked(int x, int y);

	void registerInputFieldObject(RenderObject* inputObj);
	void registerInputUnderscore(RenderObject* underscoreObj);
	void registerGuessObject(RenderObject* guessObj);
	void registerNewGameObject(RenderObject* newGameObj);
	void registerEndGameObject(RenderObject* endGameObj);

	void resetInputBox();

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

	RenderObject* m_newGame;
	RenderObject* m_exitGame;
};

