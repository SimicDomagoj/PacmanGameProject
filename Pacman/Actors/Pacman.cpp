#include "Pacman.h"

Pacman::Pacman()
{

}

int Pacman::getLives()
{
	return lives;
}

void Pacman::loseLife()
{
	lives--;
}

void Pacman::HandleInput(SDL_Event event)
{
	ic->handleInput(shared_from_this(), event);
}

void Pacman::HandleGraphics(std::shared_ptr<SDL_Renderer> renderer)
{
	gc->Render(shared_from_this(), renderer);
}

void Pacman::HandlePhysics(std::shared_ptr<PacmanMap> map)
{
	pc->Update(shared_from_this(), map);
}

SDL_Point Pacman::getSpeed()
{ 
	return speed; 
}
void Pacman::setSpeed(SDL_Point speed)
{ 
	this->speed = speed; 
}