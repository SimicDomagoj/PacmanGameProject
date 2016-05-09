#ifndef PACMAN_FACTORY
#define PACMAN_FACTORY

#include"../Actors/Pacman.h"
#include<memory>

class PacmanFactory
{
public:
	static std::shared_ptr<Pacman> getPacman(SDL_Rect initialPosition, std::shared_ptr<SDL_Renderer> renderer, std::string bitmapFile, Uint8 *colorkey = NULL);
};

#endif