#include <string>
#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <vector>
#include <sstream>
#include <string>
#include <sstream>
#include <iostream>
#pragma once

class Wordbank
{
public:

	void init();

	void pullWordsFromThesaurus();

	std::string getWordToGuess();

private:
	
	// list to hold the words we pull (we will add this to our set)
	std::vector<std::string> m_newWords;

	// use a set to store all words (set to prevent repeats)
	std::set<std::string> m_wordBank;
	
	// input will need to be parsed through to get the words
	void parseWords(std::string rawBuffer);




	
	// the purpose is to pull all of the words
	// and store all of the words we will use
	// we can use this to get the word to guess
	// the guessed letters will be handled elsewhere
	

	// will this handle the guessed letters? NO
};

// Use libcurl to pull data from the API
// function to pass into libcurl handlers (it is used whenever there is data that needs to be saved)
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData);
