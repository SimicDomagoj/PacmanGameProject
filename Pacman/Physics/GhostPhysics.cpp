#include "GhostPhysics.h"
#include"../Actors/Ghost.h"
#include"../Service/CollisionService.h"

void GhostPhysics::update(std::shared_ptr<Ghost> actor, std::shared_ptr<PacmanMap> map)
{
	eDirection direction = actor->getDirection();
	SDL_Rect position = actor->getPosition();
	SDL_Point speed{ 0, 0 };
	switch (direction)
	{
		case eDirection::DIRECTION_UP: speed.y = -Constants::speed; break;
		case eDirection::DIRECTION_DOWN: speed.y = Constants::speed; break;
		case eDirection::DIRECTION_LEFT: speed.x = -Constants::speed; break;
		case eDirection::DIRECTION_RIGHT: speed.x = Constants::speed; break;
		default: break;
	}
	position.x += speed.x; 
	if (CollisionService::checkCollision(actor, map))
	{
		position.x -= speed.x;
	}
	position.y += speed.y;
	if (CollisionService::checkCollision(actor, map))
	{
		position.y -= speed.y;
	}
	actor->setPosition(position);
}