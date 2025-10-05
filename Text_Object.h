#include "RenderObject.h"
#include <SDL3_ttf/SDL_ttf.h>
#pragma once
class Text_Object : public RenderObject
{
public:
	void init();

	int getAngle() const;
	//virtual std::string getName();
	void close();
private:
	//std::string m_name;
};

