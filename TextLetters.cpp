#include "TextLetters.h"

TextLetters::TextLetters()
{
	m_guessedLettersLabel = nullptr;
	m_possibleCharacters = {
	"_", // we will need these
	"Input:", // for the input box
	"Guessed Letters:",
	"A", "B", "C", "D", "E",
	"F", "G", "H", "I", "J",
	"K", "L", "M", "N", "O",
	"P", "Q", "R", "S", "T",
	"U", "V", "W", "X", "Y",
	"Z",
	};

	// if we want capital letters we should return the word from the word book with capitals
}

void TextLetters::init(int screenWidth, int screenHeight)
{
	//m_guessedLettersLabel->setX(screenWidth - m_guessedLettersLabel->getTextureWidth() - (m_guessedLettersLabel->getTextureWidth() / 2));
	m_guessedLettersLabel->setX(screenWidth - m_guessedLettersLabel->getTextureWidth() - 10);
	m_guessedLettersLabel->setY(0);

	// for the guessed letters
	setUpCoorForGuessedLetters(screenWidth, screenHeight);
	// for the word to guess
	setUpCoordForWordToGuess(screenWidth, screenHeight);
	// for the underscores
	setUpUnderscoresForGuess(screenWidth, screenHeight);
}

std::vector<std::string>& TextLetters::getPossibleCharacters()
{
	return m_possibleCharacters;
}

void TextLetters::registerLetters(RenderObject* curObj, std::string name)
{
	//m_guesses.emplace(name, curObj);
	// under the hood this makes a pair
	m_guesses.emplace(std::make_pair(name, curObj));

}

void TextLetters::registerWord(RenderObject* curObj)
{
	m_wordToGuess_RenderObjs.push_back(curObj);
}

void TextLetters::registerUnderscore(RenderObject* curObj)
{
	m_blankLetterSpots.push_back(curObj);
}

void TextLetters::registerGuessedLabel(RenderObject* curObj)
{
	m_guessedLettersLabel = curObj;
}

void TextLetters::setWordToGuess(std::string wordToGuess)
{
	m_wordToGuess = wordToGuess;
	m_currentGuess = wordToGuess;
	// fill up our guess state
	int i = 0;
	for (char c : m_wordToGuess)
	{
		m_currentGuess.at(i) = '_';
		i++;
	}
}

bool TextLetters::checkGuess(std::string guessedLettter)
{
	char guess = guessedLettter.at(0);
	if (checkIfNewGuess(guess))
		if (checkNewGuess(guess))
		{
			return true;
		}
		else
		{
			return false;
		}
	return true; // we don't want to penalize for past wrong guesses
}

std::string TextLetters::getCurrentGuess()
{
	return m_currentGuess;
}

void TextLetters::update()
{
	// we need to get the guessed word objects updated
	// we need to update the guessed word objects
	auto end = m_guessedLetters.end();
	for (auto iter = m_guessedLetters.begin(); iter != end; iter++)
	{
		std::string curLetter = std::string(1, iter->first);
		if (iter->second)
		{
			m_guesses[curLetter]->setVisibleFlag();
		}
		else
			m_guesses[curLetter]->unsetVisibleFlag();
	}

	for (int i = 0; i < m_currentGuess.size(); i++)
	{
		if (m_currentGuess.at(i) != '_')
			m_wordToGuess_RenderObjs.at(i)->setVisibleFlag();
	}

}

void TextLetters::close()
{
	// the objects are registerd with the renderer, which will delete them
}

std::string TextLetters::getWord() const
{
	return m_wordToGuess;
}

bool TextLetters::checkIfNewGuess(char guessedLetter)
{
	if (m_guessedLetters[guessedLetter] == false)
	{
		m_guessedLetters[guessedLetter] = true;
		return true;
	}
	return false;
}

bool TextLetters::checkNewGuess(char guessedLetter)
{
	if (isCorrectLetter(guessedLetter))
		return true;
	else
		return false;
}

bool TextLetters::isCorrectLetter(char guessedLetter)
{
	for (char c : m_wordToGuess)
	{
		if (c == guessedLetter)
		{
			m_guessedLetters.emplace(guessedLetter, true);
			updateGuessedWordState();
			return true;
		}
	}
	return false;
}

void TextLetters::setUpCoorForGuessedLetters(int screenWidth, int screenHeight)
{
	// for the guessed letters
	// we need to set the location of every object
	auto end = m_guesses.end();
	auto iter = m_guesses.begin();
	int x = screenWidth - m_guessedLettersLabel->getTextureWidth();
	int baseY = m_guessedLettersLabel->getTextureHeight();
	int y = 0 + baseY;
	for (iter; iter != end; iter++)
	{
		
		if (y > (screenHeight - 400))
		{
			x += 150;
			y = baseY;
		}
		iter->second->setX(x);
		iter->second->setY(y);
		y += 150;
	}
}

void TextLetters::setUpCoordForWordToGuess(int screenWidth, int screenHeight)
{
	// m_wordToGuess_RenderObjs
	int x = 50;
	int y = screenHeight - 200;
	int xInc = m_wordToGuess_RenderObjs[0]->getTextureWidth() * 2;
	for (int i = 0; i < m_wordToGuess_RenderObjs.size(); i++)
	{
		//m_wordToGuess_RenderObjs.at(i)->setVisibleFlag(); 
		m_wordToGuess_RenderObjs.at(i)->setX(x);
		m_wordToGuess_RenderObjs.at(i)->setY(y);
		x += xInc;
	}
}

void TextLetters::setUpUnderscoresForGuess(int screenWidth, int screenHeight)
{
	// m_blankLetterSpots
	int x = 50;
	int y = screenHeight - 200;
	int xInc = m_wordToGuess_RenderObjs[0]->getTextureWidth() * 2;
	for (int i = 0; i < m_blankLetterSpots.size(); i++)
	{
		m_blankLetterSpots.at(i)->setVisibleFlag();
		m_blankLetterSpots.at(i)->setX(x);
		m_blankLetterSpots.at(i)->setY(y);
		x += xInc;
	}
}

void TextLetters::updateGuessedWordState()
{
	int index = 0;
	for (char c : m_wordToGuess)
	{
		if (m_guessedLetters[c])
		{
			m_currentGuess.at(index) = m_wordToGuess.at(index);
		}
		index++;
	}
}
