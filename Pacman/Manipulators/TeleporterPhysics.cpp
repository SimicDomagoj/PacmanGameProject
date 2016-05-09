#include"TeleporterPhysics.h"

void TeleporterPhysics::update(std::shared_ptr<Actor> actor)
{
	SDL_Rect position = actor->getPosition();
	position.x = destination.x;
	position.y = destination.y;
	actor->setPosition(position);
}