#include"Ghost.h"

void Ghost::powerdown()
{
	ac->powerdown(shared_from_this());
}

void Ghost::die()
{
	ac->die(shared_from_this());
}

void Ghost::turnNormal()
{
	ac->turnNormal(shared_from_this());
}

void Ghost::HandleGraphics(std::shared_ptr<SDL_Renderer> renderer)
{
	gc->Render(shared_from_this(), renderer);
}

void Ghost::HandleAI(std::shared_ptr<PacmanMap> map)
{
	ac->HandleAI(shared_from_this(), map);
}

void Ghost::HandlePhysics(std::shared_ptr<PacmanMap> map)
{
	pc->update(shared_from_this(), map);
}

void Ghost::update()
{
	powerdown();
}