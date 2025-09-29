#include "RendererEngine.h"

void RendererEngine::init(SDL_Renderer* windowRenderer)
{
	m_renderer = windowRenderer;
}

void RendererEngine::drawBlock(int x, int y, int width, int height, int R, int G, int B, int A)
{
	// The rectangle shape
	SDL_FRect fillRect{ x, y, width, height };
	// The color 
	SDL_SetRenderDrawColor(m_renderer, R, G, B, A);
	// Draw the block
	SDL_RenderFillRect(m_renderer, &fillRect);
}

void RendererEngine::drawSquare(int x, int y, int width, int height, int R, int G, int B)
{
	SDL_FRect squareOutline = { x, y, width, height };
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderRect(m_renderer, &squareOutline);
}

void RendererEngine::drawQuad(int x, int y, int width, int height, SDL_Texture* textureToApply)
{
	SDL_FRect textRect = { x, y, width, height }; // rectangle where the text is drawn 
	SDL_RenderTexture(m_renderer, textureToApply, NULL, &textRect);
}

void RendererEngine::drawQuad(int x, int y, int width, int height, SDL_Texture* texture, double angle)
{
	// rectangle where the texture is drawn 
	SDL_FRect textureRect = { x, y, width, height }; 
	// cover it with the texture - NULL for default center to rotate around
	//if (angle > 0)
	SDL_FPoint center = { 0, 0 }; // top left corner
	if (angle < 0)
		center = { textureRect.w, 0 };
	SDL_RenderTextureRotated(m_renderer, texture, NULL, &textureRect, angle, &center, SDL_FLIP_NONE);
}

void RendererEngine::clearScreen()
{
	// clear the screen
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(m_renderer);
}

void RendererEngine::renderPresent()
{
	SDL_RenderPresent(m_renderer);
}

void RendererEngine::close()
{
	for (int i = m_registeredList.size() - 1; i >= 0; i--)
	{
		delete m_registeredList.at(i);
		m_registeredList.at(i) = nullptr;
		m_registeredList.pop_back();
	}
	SDL_DestroyRenderer(m_renderer);
}

SDL_Renderer* RendererEngine::getRenderer()
{
	return m_renderer;
}

void RendererEngine::registerObj(RenderObject* obj)
{
	m_registeredList.push_back(obj);
}

void RendererEngine::unRegisterObj(RenderObject* obj)
{
	auto i = find(m_registeredList.begin(), m_registeredList.end(), obj);
	m_registeredList.erase(i);
	delete obj;
	obj = nullptr;
}

//void RendererEngine::drawObjects(int (*pf_convertCoors)(int))
void RendererEngine::drawObjects(int factor)
{
	for (int i = 0; i < m_registeredList.size(); i++)
	{
		RenderObject* curObj = m_registeredList.at(i);
		if (curObj->getVisibleFlag())
		{
			if (!curObj->isDrawAtAngle())
			{
				//int x = pf_convertCoors(curObj->getX());
				//int y = pf_convertCoors(curObj->getY());
				int x, y;
				//curObj->convertCoordinates(x, y, factor);
				x = curObj->getX();
				y = curObj->getY();

				drawQuad(x, y, curObj->getTextureWidth(), curObj->getTextureHeight(), curObj->getTexture().get());
				
			}
			else
			{
				// draw at angle
				int x, y;
				//curObj->convertCoordinates(x, y, factor);
				x = curObj->getX();
				y = curObj->getY();

				drawQuad(x, y, curObj->getTextureWidth(), curObj->getTextureHeight(), curObj->getTexture().get(), curObj->getAngle());
			}
		}
	}
}




