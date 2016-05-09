#ifndef OBJECT_GRAPHICS_COMPONENT
#define OBJECT_GRAPHICS_COMPONENT

#include<memory>
#include"../Image/Image.h"
#include<SDL.h>
#include<string>

class GameObject;

class ObjectGraphicsComponent
{
protected:
	Image bitmap;
public:
	ObjectGraphicsComponent() = delete;
	ObjectGraphicsComponent(std::string filename, std::shared_ptr<SDL_Renderer> renderer, Uint8 *colorkey = NULL)
	{
		bitmap.load_image(filename, renderer, colorkey);
	}
	virtual void Render(std::shared_ptr<GameObject> object, std::shared_ptr<SDL_Renderer> renderer) = 0;
};

#endif