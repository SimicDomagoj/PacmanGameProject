#ifndef SIMPLE_GRAPHICS_COMPONENT
#define SIMPLE_GRAPHICS_COMPONENT

#include"ObjectGraphicsComponent.h"
#include"../Objects/GameObject.h"

class SimpleGraphicsComponent : public ObjectGraphicsComponent
{
public:
	SimpleGraphicsComponent() = delete;
	SimpleGraphicsComponent(std::string filename, std::shared_ptr<SDL_Renderer> renderer, Uint8 *colorkey = NULL) : ObjectGraphicsComponent(filename, renderer, colorkey) {}
	void Render(std::shared_ptr<GameObject> object, std::shared_ptr<SDL_Renderer> renderer) override
	{
		SDL_Rect position = object->getPosition();
		bitmap.apply_surface(renderer, position.x, position.y, NULL);
	};
};

#endif