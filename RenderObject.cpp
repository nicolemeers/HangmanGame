#include "RenderObject.h"

void RenderObject::setVisibleFlag()
{
	m_isVisibleFlag = true;
}

void RenderObject::unsetVisibleFlag()
{
	m_isVisibleFlag = false;
}

bool RenderObject::getVisibleFlag()
{
	return m_isVisibleFlag;
}

bool RenderObject::isDrawAtAngle() const
{
	return m_drawAtAngle;
}

void RenderObject::setName(std::string name)
{
	m_name = name;
}

int RenderObject::getX() const
{
	return m_x;
}

int RenderObject::getY() const
{
	return m_y;
}

void RenderObject::setX(int x)
{
	m_x = x;
}

void RenderObject::setY(int y)
{
	m_y = y;
}

int RenderObject::getTextureWidth() const
{
	return m_textureWidth;
}

int RenderObject::getTextureHeight() const
{
	return m_textureHeight;
}

void RenderObject::convertCoordinates(int& x, int& y, int factorOfGrid) const
{
	// xSize = screenWidth / someNum
	// => someNum = screenWidth / xSize
	x = m_x * factorOfGrid;
	y = m_y * factorOfGrid;
}

void RenderObject::setTexture(std::shared_ptr<SDL_Texture> texture)
{
	m_texture = texture;
	setTextureDimensions(texture->w, texture->h);
}

void RenderObject::setTextureDimensions(int w, int h)
{
	m_textureWidth = w;
	m_textureHeight = h;
}

std::shared_ptr<SDL_Texture> RenderObject::getTexture()
{
	return m_texture;
}
