//#include "RendererEngine.h"
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <memory>
#pragma once
class RenderObject
{
public:
	// all render objects need to:
	virtual void init() = 0;
	
	// if we need to render the object or not
	void setVisibleFlag();
	void unsetVisibleFlag();
	bool getVisibleFlag();

	bool isDrawAtAngle() const;
	virtual int getAngle() const = 0;

	void setName(std::string name);

	int getX() const;
	int getY() const;

	void setX(int x);
	void setY(int y);

	int getTextureWidth() const;
	int getTextureHeight() const;

	// make sure the coordinates passed to the renderer are the actual window coordinates
	void convertCoordinates(int& x, int& y, int factorOfGrid) const;
	// set the texture (and texture dimensions) for the object
	void setTexture(std::shared_ptr<SDL_Texture> texture);
	void setTextureDimensions(int w, int h);

	std::shared_ptr<SDL_Texture> getTexture();
	
	// make sure everything is deallocated and closed when the object is finished
	virtual void close() = 0;

protected:
	// flag for if we render the object or not
	bool m_isVisibleFlag;
	// coordinates
	int m_x, m_y;

	// for the texture
	std::shared_ptr<SDL_Texture> m_texture;
	int m_textureWidth;
	int m_textureHeight;

	std::string m_name;

	bool m_drawAtAngle;
	int m_angle = 0;

	// we could make a render object for each piece 
	// each object has its pointer to the texture
	// we would register each object with the renderer engine and unregister
	// so they'll be created in main, the engine will have the object
	// we do our render call and it'll render each object
		// do something like check for the angle to call the draw at an angle call instead
			// but that image is at an angle, so maybe not
	// so once registered, the rendererengine will have a pointer to this object
	// and it can loop through all of the objects, check if they're visible, and then render them
	// yes, so we register, and the renderer knows what objects it will need to render


	/*
	In immediate-mode, on every frame, each object makes a call into the rendering system to render itself. It is the 
	program's responsibility to go around to every object to give them a chance to do so.

	In retained-mode, you have a data structure like a vector or a scene graph which is maintained (i.e. 'retained') 
	by the rendering engine. Then, every frame, the rendering engine knows all the objects that may need to be rendered, 
	and iterates through them. This also has the advantage that the renderer may be able to optimize the rendering by 
	re-ordering and batching.
	*/


};

