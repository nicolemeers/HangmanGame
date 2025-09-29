#include <map>
#include "Gallows_Object.h"
#pragma once
class GallowsMan
{
public:
	GallowsMan();

	void init(int screenWidth, int screenHeight);

	std::vector<std::string>& getImagesToDraw();

	//void addToMap
	void registerToMap(RenderObject* renderObj, std::string name);
	void registerGameEndText(RenderObject* renderObj, std::string name);

	// there was a wrong guess -> update the state
	void updateGallows();
	// get the current state of the gallows
	int getCurrentState() const;
	
	void setWinState();

	void resetState();
	// the gallowobject will be a visual component, and this will be the logic component

	// this could be responsible for what gallows shapes to put up
	// for example, this could store the state of the gallows, 
	// and every time the number of chances decreases, we 
	// update the state, and when the state changes that's how we
	// know the next thing to render/set as visible

	// so this will also store all of the images for the texture handler to deal with

	void close();


private:
	std::vector<std::string> m_imagesToDisaply;
	int m_currentState;
	//int m_chancesRemaining;
	// use a map for the render objects, since they will all have a unique name
	std::map<std::string, Gallows_Object*> m_displayObjects;
	
	//RenderObject* m_chancesRemaining;
	RenderObject* m_gameOver;
	RenderObject* m_gameWon;
};

