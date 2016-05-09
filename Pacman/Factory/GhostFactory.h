#ifndef GHOST_FACTORY
#define GHOST_FACTORY

#include<memory>
#include"../Actors/Ghost.h"

class GhostFactory
{
public:
	static std::shared_ptr<Ghost> getGhost(eGhost type, SDL_Rect initialPosition, std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Actor> actor, std::shared_ptr<Ghost> ghostFollow = nullptr);
};

#endif