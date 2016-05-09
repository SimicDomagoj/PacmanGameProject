#ifndef GHOST_GRAPHICS
#define GHOST_GRAPHICS

#include"../Image/Image.h"
#include<memory>

class Ghost;

class GhostGraphics
{
protected:
	Image bitmap;
public:
	GhostGraphics(std::string filename, std::shared_ptr<SDL_Renderer> renderer, Uint8 *colorkey = NULL)
	{
		bitmap.load_image(filename, renderer, colorkey);
	}
	void Render(std::shared_ptr<Ghost> actor, std::shared_ptr<SDL_Renderer> renderer);
};

#endif