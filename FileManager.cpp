#include "FileManager.h"

void FileManager::init()
{
}

bool FileManager::readFile(const std::string& filePath, std::vector<std::string>& dataToRead)
{
    if (checkIfFileExists(filePath))
    {
        m_dictionaryFile.open(filePath, std::fstream::in);
        if (m_dictionaryFile.is_open())
        {
            // read the file
            // will be length of file (# words)
            // name (dictionary)
            std::string header = "";
            getline(m_dictionaryFile, header);

            std::istringstream h(header);
            std::string token = "";

            std::getline(h, token, ',');
            int size = std::stoi(token);
            dataToRead = std::vector<std::string>(size, "");
            getline(m_dictionaryFile, header);

            std::string curLine = "";
            int index = 0;
            while (getline(m_dictionaryFile, curLine))
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
            m_dictionaryFile.close();
            return true;
        }
        else
            std::cerr << "Error: Could not open file: " << filePath << "\n";
        
    }
    else
        std::cerr << "Error: File " << filePath << " does not exist\n";
    return false;
}

bool FileManager::writeFile(const std::string& filePath, std::vector<std::string>& dataToWrite)
{
    if (checkIfFileExists(filePath))
    {
        m_dictionaryFile.open(filePath, std::fstream::out);
        if (m_dictionaryFile.is_open())
        {
            int size = dataToWrite.size();
            // write out the header information
            // for now:
            m_dictionaryFile << size << "," << "dictionary\n";

            // content
            for (int i = 0; i < size; i++)
            {
                if (i == size - 1)
                    m_dictionaryFile << dataToWrite[i] << "\n";
                else if (i % 5 == 0)
                {
                    m_dictionaryFile << dataToWrite[i] << "\n";
                }
                else
                {
                    m_dictionaryFile << dataToWrite[i] << ",";
                }
            }
            m_dictionaryFile.close();
            return true;
        }
        else
            std::cerr << "Error: Could not open file: " << filePath << "\n";
    }
    else
        std::cerr << "Error: File " << filePath << " does not exist\n";
    return false;
}

bool FileManager::addToFile(const std::string& filePath, std::vector<std::string>& dataToAppend)
{
    if (checkIfFileExists(filePath))
    {
        m_dictionaryFile.open(filePath, std::fstream::out | std::fstream::app);
        if (m_dictionaryFile.is_open())
        {
            int size = dataToAppend.size();
            // write out the header information
            // for now:
            m_dictionaryFile << size << "," << "dictionary\n";

            // content
            for (int i = 0; i < size; i++)
            {
                if (i == size - 1)
                    m_dictionaryFile << dataToAppend[i] << "\n";
                else if (i % 5 == 0)
                {
                    m_dictionaryFile << dataToAppend[i] << "\n";
                }
                else
                {
                    m_dictionaryFile << dataToAppend[i] << ",";
                }
            }
            m_dictionaryFile.close();
            return true;
        }
        else
            std::cerr << "Error: Could not open file: " << filePath << "\n";
    }
    else
        std::cerr << "Error: File " <<  filePath << " does not exist\n";
    return false;
}

bool FileManager::addToFile(const std::string& filePath, std::set<std::string>& dataToAppend)
{
    if (checkIfFileExists(filePath))
    {
        m_dictionaryFile.open(filePath, std::fstream::out | std::fstream::app);
        if (m_dictionaryFile.is_open())
        {
            int size = dataToAppend.size();
            auto iter = dataToAppend.begin();
            auto end = dataToAppend.end();
            // write out the header information
            // for now:
            m_dictionaryFile << size << "," << "dictionary\n";

            // content
            //for (int i = 0; i < size; i++)
            int i = 0;
            for (iter; iter != end; iter++)
            {
                if (i == size - 1)
                    m_dictionaryFile << *iter << "\n";
                else if (i % 5 == 0)
                {
                    m_dictionaryFile << *iter << "\n";
                }
                else
                {
                    m_dictionaryFile << *iter << ",";
                }
            }
            m_dictionaryFile.close();
            return true;
        }
        else
            std::cerr << "Error: Could not open file: " << filePath << "\n";
    }
    else
        std::cerr << "Error: File " << filePath << " does not exist\n";
    return false;
}

bool FileManager::checkIfFileExists(const std::string& filePath)
{
    if (std::filesystem::exists(filePath))
        return true;
    return false;
}

bool FileManager::createFile(const std::string& filePath)
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

bool FileManager::deleteFile(const std::string& filePath)
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
    //m_dictionaryFile.close();
}
