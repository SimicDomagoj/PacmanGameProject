#include"PacmanFactory.h"
#include"../Physics/PacmanPhysics.h"
#include"../Input/PacmanInput.h"
#include"../Graphics/PacmanGraphics.h"

std::shared_ptr<Pacman> PacmanFactory::getPacman(SDL_Rect initialPosition, std::shared_ptr<SDL_Renderer> renderer, std::string bitmapFile, Uint8 *colorkey)
{
	std::shared_ptr<Pacman> p = std::make_shared<Pacman>();
	p->setPosition(initialPosition);
	p->setPhysicsComp(std::make_shared<PacmanPhysics>());
	p->setInputComp(std::make_shared<PacmanInput>());
	p->setGraphicsComp(std::make_shared<PacmanGraphics>(bitmapFile, renderer, colorkey));
	return p;
}