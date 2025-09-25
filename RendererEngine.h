#include <SDL3/SDL.H>
//#include <SDL3/SDL_main.h>
#include "RenderObject.h"
#pragma once
class RendererEngine
{
public:
	void init(SDL_Renderer* windowRenderer);
	void drawBlock(int x, int y, int width, int height, int R, int G, int B, int A);
	void drawSquare(int x, int y, int width, int height, int R, int G, int B);
	void drawQuad(int x, int y, int width, int height, SDL_Texture* textureToApply);
	// to draw the quad at an angle
	void drawQuad(int x, int y, int width, int height, SDL_Texture* texture, double angle);

	void clearScreen();
	void renderPresent();

	void close();
	SDL_Renderer* getRenderer();

	void registerObj(RenderObject* obj);
	void unRegisterObj(RenderObject* obj);

	//void drawObjects(int (*pf_convertCoors)(int));
	void drawObjects(int factor);
private:

	SDL_Renderer* m_renderer = NULL;
	std::vector<RenderObject*> m_registeredList;

};

