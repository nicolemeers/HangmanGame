#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <set>
#pragma once
class FileManager
{
public:
	void init();
	
	bool readFile(std::string filePath, std::vector<std::string>& dataToRead);
	bool writeFile(std::string filePath, std::vector<std::string>& dataToWrite);
	bool addToFile(std::string filePath, std::vector<std::string>& dataToAppend);
	bool addToFile(std::string filePath, std::set<std::string>& dataToAppend);

	bool checkIfFileExists(std::string filePath);
	bool createFile(std::string filePath);
	bool deleteFile(std::string filePath);

	void close();
private:
	
	std::fstream f;
};

