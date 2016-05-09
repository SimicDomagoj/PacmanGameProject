#ifndef PACMAN_INPUT
#define PACMAN_INPUT

#include"InputComponent.h"

class PacmanInput : public InputComponent
{
public:
	void handleInput(std::shared_ptr<Actor> actor, SDL_Event event) override;
};

#endif