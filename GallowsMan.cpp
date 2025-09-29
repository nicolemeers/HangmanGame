#include "GallowsMan.h"

enum gallowsState
{
	START = 0,
	GROUND,
	BASE,
	TOP,
	SUPPORT,
	HANGBEAM,
	HEAD,
	BODY,
	LEFT_ARM,
	RIGHT_ARM,
	LEFT_LEG,
	RIGHT_LEG,
	// this may be unnecessary
	DEATH
};

GallowsMan::GallowsMan()
{
	m_currentState = START;
	m_imagesToDisaply =
	{
		"01_Gallows_Ground.png",
		"02_Gallows_Base.png",
		"03_Gallows_Top.png",
		"04_Gallows_Support.png",
		"05_Gallows_HangBeam.png",
		// For the body of the hangman
		"06_Gallows_Hang_Head.png",
		"07_Gallows_Hang_Body.png",
		"08_Gallows_Hang_Arm_Left.png",
		"09_Gallows_Hang_Arm_Right.png",
		"10_Gallows_Hang_Leg_Left.png",
		"11_Gallows_Hang_Leg_Right.png"
	};
}

void GallowsMan::init(int screenWidth, int screenHeight)
{
	m_displayObjects["08_Gallows_Hang_Arm_Left.png"]->setDrawAtAngle(45);
	m_displayObjects["09_Gallows_Hang_Arm_Right.png"]->setDrawAtAngle(-45);
	m_displayObjects["10_Gallows_Hang_Leg_Left.png"]->setDrawAtAngle(45);
	m_displayObjects["11_Gallows_Hang_Leg_Right.png"]->setDrawAtAngle(-45);

	// we need to set the location of every object
	auto end = m_displayObjects.end();
	auto iter = m_displayObjects.begin();
	int x = iter->second->getTextureWidth();
	int y = screenHeight - 600;
	int i = 0;
	for (iter; iter != end; iter++)
	{
		if (iter->first == "05_Gallows_HangBeam.png")
		{
			x += m_displayObjects["03_Gallows_Top.png"]->getTextureWidth();
			x -= iter->second->getTextureWidth();
		}
		if (i == 1)
			y -= 900;
		if (i == 5 )
		{
			y += (iter->second->getTextureHeight() / 2) + 30;
			x -= 90;
		}
		if (i == 6)
		{
			y += 175;
			x += 50;
		}
		if (i == 7)
			y += 50;
		if (i == 9)
			y += 300;
		iter->second->setX(x);
		iter->second->setY(y);
		i++;
	}
}

std::vector<std::string>& GallowsMan::getImagesToDraw()
{
	return m_imagesToDisaply;
}

void GallowsMan::registerToMap(RenderObject* renderObj, std::string name)
{
	// we should only use static cast if we're certain that we will be getting a gallows_object
	// otherwise, dynamic_cast
	m_displayObjects.emplace(name, static_cast<Gallows_Object*>(renderObj));
	//m_displayObjects.emplace(std::make_pair(name, static_cast<Gallows_Object*>(renderObj)));
}

void GallowsMan::registerGameEndText(RenderObject* renderObj, std::string name)
{
	renderObj->setX(850);
	renderObj->setY(600);
	if (name == "Game Win")
	{
		m_gameWon = renderObj;
		//m_gameWon->setName(name);
	}
	else
	{
		m_gameOver = renderObj;
		//m_gameOver->setName(name);
	}
}

void GallowsMan::updateGallows()
{
	if (m_currentState == DEATH || m_currentState == RIGHT_LEG)
	{
		m_gameOver->setVisibleFlag();
		return;
	}
	
	auto iter = m_displayObjects.begin();
	for (int i = 0; i < m_currentState; i++) iter++;
	iter->second->setVisibleFlag();
	m_currentState++;
}

int GallowsMan::getCurrentState() const
{
	return m_currentState;
}

void GallowsMan::setWinState()
{
	m_gameWon->setVisibleFlag();
}

void GallowsMan::resetState()
{
	// clear text
	m_gameOver->unsetVisibleFlag();
	m_gameWon->unsetVisibleFlag();
	// reset gallows
	m_currentState = START;
	auto iter = m_displayObjects.begin();
	auto end = m_displayObjects.end();
	for (iter; iter != end; iter++)
		iter->second->unsetVisibleFlag();
}

void GallowsMan::close()
{
	// the renderer will destroy the pointers
}
