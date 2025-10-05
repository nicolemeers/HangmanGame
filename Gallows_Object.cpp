#include "Gallows_Object.h"

void Gallows_Object::init()
{
	m_angle = 0;
	m_drawAtAngle = false;
	m_isVisibleFlag = false;
}

void Gallows_Object::setDrawAtAngle(int angle)
{
	m_drawAtAngle = true;
	m_angle = angle;
}

int Gallows_Object::getAngle() const
{
	return m_angle;
}

void Gallows_Object::close()
{
}

Gallows_Object::~Gallows_Object()
{
}
