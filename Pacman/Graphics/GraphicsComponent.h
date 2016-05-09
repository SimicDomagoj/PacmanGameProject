#ifndef GRAPHICS_COMPONENT
#define GRAPHICS_COMPONENT

#include<memory>
#include"../Actors/Actor.h"
#include"../Image/Image.h"

class GraphicsComponent
{
protected:
	Image bitmap;
public:
	GraphicsComponent() = delete;
	GraphicsComponent(std::string filename, std::shared_ptr<SDL_Renderer> renderer, Uint8 *colorkey = NULL)
	{
		bitmap.load_image(filename, renderer, colorkey);
	}
	virtual void Render(std::shared_ptr<Actor> actor, std::shared_ptr<SDL_Renderer> renderer) = 0;
};

#endif