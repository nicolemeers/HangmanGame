#include "Wordbank.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData)
{
	// we can store everything in a large string and then parse it out later
	// this way, we don't have to define a memory block and allocate to it
	size_t totalSize = size * nmemb;
	userData->append((char*)contents, totalSize);
	return totalSize;
}

Wordbank::Wordbank()
{
	m_localDictionary = "./dictionary.csv";
	m_hasLocalCopy = false;
}

void Wordbank::Init()
{
	m_fileMngr = new FileManager();
	m_fileMngr->init();
	// we need to check if we have a cached local version first
	// if not then we use the API
	if (m_fileMngr->readFile(m_localDictionary, m_newWords))
	{
		m_hasLocalCopy = true;
	}
	else
	{
		// set up our vector (our base words)
		m_newWords =
		{ "syzygy", "abatis", "controvert", "controversy", "contuse", "luminary", "overt",
			"narcissism", "happy", "elegant", "poor", "bee", "helicopter", "fast", "fortuitous",
			"sequacious", "lascivious", "lecherous", "pulchritudinous", "ineffable", "jubilee",
			"jazz", "rythm", "capricious", "avarice", "greed", "serendipitous", "misanthrope",
			"taciturn", "aloof", "callous", "cynical", "callow", "sad", "gallows", "perhaps",
			"melifluous","sonorous", "egress", "somber", "solemn", "gallant", "dour", "din",
			"eccentric", "epitome", "inundate", "deluged", "frenetic", "dessicated", "wry", "sly",
			"wend", "gallant", "salacious", "scrupulous", "dubious", "objurgate", "happy", "sad",
			"splendid", "sublime", "monotonous", "melancholic", "melodious", "bird", "songbird",
			"rhythm", "silly", "boring", "ubiquitous", "omnipresence", "lovely", "sublime", "happy",
			"obfuscate", "rythm", "objurgate", "slink", "flick", "gore", "coagulate", "flower", "tree",
			"young", "suffuse"
		};

		// we need to ensure our base words are in our "bank" of words as well
		m_wordBank = std::set<std::string>(m_newWords.begin(), m_newWords.end());

		// we need to create our local copy
		m_fileMngr->createFile(m_localDictionary);
	}
}

void Wordbank::PullWordsFromThesaurus()
{
	if (m_hasLocalCopy)
		PullWordsFromThesaurusLocal();
	else
		PullWordsFromThesaurusAPI();

}

std::string& Wordbank::GetWordToGuess()
{
	srand(time(0));
	if (m_newWords.size() > m_wordBank.size())
	{
		int randIndex = rand() % m_newWords.size();
		std::string word = m_newWords.at(randIndex);
		return word;
	}
	else
	{
		int randIndex = rand() % m_wordBank.size();
		auto iterToWord = next(m_wordBank.begin(), randIndex);
		std::string word = *iterToWord;
		return word;
	}

}

Wordbank::~Wordbank()
{
	m_fileMngr->close();
	delete m_fileMngr;
}

void Wordbank::PullWordsFromThesaurusAPI()
{
	// this will be using libcurl to fill out our selection of words

	// current curl handle to store information
	CURL* curl;
	CURLcode res;
	// buffer to store the response that we will parse out
	std::string readWordsIn;
	// the API key we will need to pass in
	const std::string apiKey = "kQ42SFV0U4OBvkhl/Xs4bA==ydvsN2xplko210hC";
	// word to store the current word we are passing to the thesaurus
	std::string word = "";

	// we do not need to do global curl init
	auto setEnd = m_newWords.end();
	for (auto iter = m_newWords.begin(); iter != setEnd; iter++)
	{
		// reset our string for the next word
		readWordsIn = "";

		// initialize the current curl session
		curl = curl_easy_init();

		// get the current word for the API request
		word = *iter;;

		// construct the url with the word we are looking up
		const std::string apiUrl = "https://api.api-ninjas.com/v1/thesaurus?word=" + word;

		// tell libcurl how to behave: pass url pointer to work with, and set it up so we can pass the API Key
		curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());


		// we need to send the request headers so we can get the data from the API
		// in this case, we need to send the API key over
		struct curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, ("X-Api-Key: " + apiKey).c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		// Set the callback function to write response data
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readWordsIn);

		// send the URL/HTTP request
		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			// cerr means character error; use cerr to display errors
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n"; // endl;
		}
		else
		{
			// we were able to get the response back
			// we need to parse the response into a format that we can enter into our word bank
			ParseWords(readWordsIn);
		}

		// cleanup the current session
		curl_easy_cleanup(curl);
		//The list should be freed again(after usage) with curl_slist_free_all (the linked list of strings is added to with curl_slist_append)
		curl_slist_free_all(headers);
	}

	// always cleanup
	curl_global_cleanup();

	// we need to write this to our local cache
	WriteToLocalCopy();
}

void Wordbank::PullWordsFromThesaurusLocal()
{
	m_fileMngr->readFile(m_localDictionary, m_newWords);
}

void Wordbank::ParseWords(std::string rawBuffer)
{
	// we know we get the response in JSON format, and need to parse it out

	std::string wordToken = "temp";
	std::string formatToken = "";
	std::stringstream parseS(rawBuffer);

	// deal with the opening format of the response
	getline(parseS, formatToken, '[');
	while (wordToken != "")
	{
		// skip the quotation marks
		getline(parseS, formatToken, '"');

		// check if there is a bracket
		if (formatToken.find("]") != std::string::npos)
		{
			// check if it's the end or the antonym switch
			if (formatToken.find("}") != std::string::npos)
				break;

			// antonym switch - skip formatting and get to the next 
			getline(parseS, formatToken, '[');
			getline(parseS, formatToken, '"');
		}

		// get the word
		getline(parseS, wordToken, '"');

		bool isValidWord = true;

		// check the word for weird tokens -> do not add (some words have accented letters, which are displayed with numbers and slashes in the string)
		for (int i = 0; i < wordToken.size(); i++)
		{
			if (!isalpha(wordToken.at(i)))
			{
				isValidWord = false;
				break;
			}
		}

		// add the word into our set
		if (isValidWord)
			m_wordBank.emplace(wordToken);

	}
}

void Wordbank::WriteToLocalCopy()
{
	m_fileMngr->addToFile(m_localDictionary, m_wordBank);
}
