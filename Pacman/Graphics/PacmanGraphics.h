#ifndef PACMAN_GRAPHICS
#define PACMAN_GRAPHICS

#include"GraphicsComponent.h"
#include"../Timer/Timer.h"

class PacmanGraphics : public GraphicsComponent
{
protected:
	int frame{ 0 };
	Timer showNext;
public:
	PacmanGraphics() = delete;
	PacmanGraphics(std::string filename, std::shared_ptr<SDL_Renderer> renderer, Uint8 *colorkey = NULL) : GraphicsComponent(filename, renderer, colorkey) { showNext.start(); }
	void Render(std::shared_ptr<Actor> actor, std::shared_ptr<SDL_Renderer> renderer) override;
};

#endif