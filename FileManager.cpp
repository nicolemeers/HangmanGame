#include "FileManager.h"

void FileManager::init()
{
}

bool FileManager::readFile(std::string filePath, std::vector<std::string>& dataToRead)
{
    if (checkIfFileExists(filePath))
    {
        f.open(filePath, std::fstream::in);
        if (f.is_open())
        {
            // read the file
            // will be length of file (# words)
            // name (dictionary)
            std::string header = "";
            getline(f, header);

            std::istringstream h(header);
            std::string token = "";

            std::getline(h, token, ',');
            int size = std::stoi(token);
            dataToRead = std::vector<std::string>(size, "");
            getline(f, header);

            std::string curLine = "";
            int index = 0;
            while (getline(f, curLine))
            {
                std::istringstream s(curLine);
                
                while (std::getline(s, token, ','))
                {
                    dataToRead[index] = token;
                    index++;
                }
                // get the last one
                //std::getline(s, token);
                //dataToRead[index] = token;
            }
            f.close();
            return true;
        }
        else
            std::cerr << "Error: Could not open file: " << filePath << "\n";
        
    }
    else
        std::cerr << "Error: File " << filePath << " does not exist\n";
    return false;
}

bool FileManager::writeFile(std::string filePath, std::vector<std::string>& dataToWrite)
{
    if (checkIfFileExists(filePath))
    {
        f.open(filePath, std::fstream::out);
        if (f.is_open())
        {
            int size = dataToWrite.size();
            // write out the header information
            // for now:
            f << size << "," << "dictionary\n";

            // content
            for (int i = 0; i < size; i++)
            {
                if (i == size - 1)
                    f << dataToWrite[i] << "\n";
                else if (i % 5 == 0)
                {
                    f << dataToWrite[i] << "\n";
                }
                else
                {
                    f << dataToWrite[i] << ",";
                }
            }
            f.close();
            return true;
        }
        else
            std::cerr << "Error: Could not open file: " << filePath << "\n";
    }
    else
        std::cerr << "Error: File " << filePath << " does not exist\n";
    return false;
}

bool FileManager::addToFile(std::string filePath, std::vector<std::string>& dataToAppend)
{
    if (checkIfFileExists(filePath))
    {
        f.open(filePath, std::fstream::out | std::fstream::app);
        if (f.is_open())
        {
            int size = dataToAppend.size();
            // write out the header information
            // for now:
            f << size << "," << "dictionary\n";

            // content
            for (int i = 0; i < size; i++)
            {
                if (i == size - 1)
                    f << dataToAppend[i] << "\n";
                else if (i % 5 == 0)
                {
                    f << dataToAppend[i] << "\n";
                }
                else
                {
                    f << dataToAppend[i] << ",";
                }
            }
            f.close();
            return true;
        }
        else
            std::cerr << "Error: Could not open file: " << filePath << "\n";
    }
    else
        std::cerr << "Error: File " <<  filePath << " does not exist\n";
    return false;
}

bool FileManager::addToFile(std::string filePath, std::set<std::string>& dataToAppend)
{
    if (checkIfFileExists(filePath))
    {
        f.open(filePath, std::fstream::out | std::fstream::app);
        if (f.is_open())
        {
            int size = dataToAppend.size();
            auto iter = dataToAppend.begin();
            auto end = dataToAppend.end();
            // write out the header information
            // for now:
            f << size << "," << "dictionary\n";

            // content
            //for (int i = 0; i < size; i++)
            int i = 0;
            for (iter; iter != end; iter++)
            {
                if (i == size - 1)
                    f << *iter << "\n";
                else if (i % 5 == 0)
                {
                    f << *iter << "\n";
                }
                else
                {
                    f << *iter << ",";
                }
            }
            f.close();
            return true;
        }
        else
            std::cerr << "Error: Could not open file: " << filePath << "\n";
    }
    else
        std::cerr << "Error: File " << filePath << " does not exist\n";
    return false;
}

bool FileManager::checkIfFileExists(std::string filePath)
{
    if (std::filesystem::exists(filePath))
        return true;
    return false;
}

bool FileManager::createFile(std::string filePath)
{
    std::ofstream createdFile(filePath);
    if (createdFile.is_open())
    {
        createdFile.close();
        return true;
    }
    std::cerr << "Error: Could not create file: " << filePath << "\n";
    return false;
}

bool FileManager::deleteFile(std::string filePath)
{
    if (checkIfFileExists(filePath))
    {
        if (std::filesystem::remove(filePath)) 
            return true; 
        //try 
        //{
        //    if (std::filesystem::remove(filePath)) { return true; }
        //}
        //catch (const std::filesystem::filesystem_error& err)
        //{
        //    std::cerr << "Filesystem error: " << err.what() << "\n";
        //}
    }
    std::cerr << "Error: File " << filePath <<" does not exist\n";
    return false;
}

void FileManager::close()
{
    //f.close();
}
