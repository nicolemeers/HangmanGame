#include <unordered_map>
#include <map>
#include "RendererEngine.h"
#include "RenderObject.h"
#pragma once
class TextLetters
{
public:
	TextLetters();

	void init(int screenWidth, int screenHeight);
	
	std::vector<std::string>& getPossibleCharacters();

	void registerLetters(RenderObject* curObj, std::string name);
	void registerWord(RenderObject* curObj);
	void registerUnderscore(RenderObject* curObj);
	void registerGuessedLabel(RenderObject* curObj);

	// save the word for the game
	void setWordToGuess(std::string wordToGuess);
	std::string getWord() const;

	// we are going to check if this letter is a good guess
	// it will also check if this letter has been guessed already (to avoid double striking)
	bool checkGuess(std::string guessedLettter);

	// return the current guess state 
	std::string getCurrentGuess();

	void update();
	void reset(RendererEngine* renderer);
	void resetWordToGuess(int screenWidth, int screenHeight);

	bool checkIfWordIsComplete() const;
	void showFullWord();

	void close();

private:
	std::vector<std::string> m_possibleCharacters;
	// the word with the guesses in it
	std::string m_currentGuess;
	// the word we are trying to guess
	std::string m_wordToGuess;
	// all of the guesses that have been made
	std::unordered_map<char, bool> m_guessedLetters;
	
	// make sure that what we show is up to date
	void updateGuessedWordState();

	// guess verification
	bool checkIfNewGuess(char guessedLetter);
	bool checkNewGuess(char guessedLetter);
	// check if this letter is in the word we are trying to guess
	bool isCorrectLetter(char guessedLetter);

	void setUpCoorForGuessedLetters(int screenWidth, int screenHeight);
	void setUpCoordForWordToGuess(int screenWidth, int screenHeight);
	void setUpUnderscoresForGuess(int screenWidth, int screenHeight);

	// use a vector since we can have multiple objects with the same "name"
	// we will use a vector for the word and a map for the possible characters
	RenderObject* m_guessedLettersLabel;
	std::vector<RenderObject*> m_wordToGuess_RenderObjs;
	std::vector<RenderObject*> m_blankLetterSpots;
	std::map<std::string, RenderObject*> m_guesses;
};

