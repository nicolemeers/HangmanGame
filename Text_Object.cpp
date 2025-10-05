#include "Text_Object.h"

void Text_Object::init()
{
	m_isVisibleFlag = false;
	m_angle = 0;
}

int Text_Object::getAngle() const
{
	return 0;
}

void Text_Object::close()
{
}




//void Text_Letters::setupContainerForSurfaces()
//{
//	// Need the underscore for the hangman display
//	m_thingToDisplay.push_back("_");
//	for (char c : m_wordToDisplay)
//	{
//		m_thingToDisplay.push_back(std::string(1, c));
//	}
//
//	/*for (int i = 0; i < m_wordToDisplay.size(); i++)
//	{
//		m_thingToDisplay.push_back(std::string(1, m_wordToDisplay[i]));
//	}*/
//	
//}
