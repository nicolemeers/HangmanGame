#include "RenderObject.h"
#pragma once
class Gallows_Object : public RenderObject
{
public:
	//Gallows_Object();

	void init();

	void setDrawAtAngle(int angle);
	int getAngle();

	void close();

	~Gallows_Object();

private:

	// if we need to draw at an angle



	//std::vector<std::string> m_imagesToReadIn;

	// so first we need to make a surface from the texture
	

	// then we need to make a texture from the surface

	// we need ground, base, top, cross bar, rope/hang bar

	// then we need the man
	// head, body, left arm, right arm, left leg, right leg
	
	// these will go into resource files
};

