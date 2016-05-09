#include"PacmanPhysics.h"
#include"../Service/CollisionService.h"

void PacmanPhysics::Update(std::shared_ptr<Actor> actor, std::shared_ptr<PacmanMap> map)
{
	SDL_Rect offset = actor->getPosition();
	SDL_Point speed = actor->getSpeed();
	eDirection direction = actor->getDirection(), newDirection = actor->getDirection();
	offset.x += speed.x;
	actor->setPosition(offset);
	if (CollisionService::checkCollision(actor, map))
	{
		offset.x -= speed.x;
		speed.x = 0;
	}
	if (speed.x > 0)
	{
		newDirection = eDirection::DIRECTION_RIGHT;
	}
	else if (speed.x < 0)
	{
		newDirection = eDirection::DIRECTION_LEFT;
	}

	offset.y += speed.y;
	actor->setPosition(offset);
	if (CollisionService::checkCollision(actor, map))
	{
		offset.y -= speed.y;
		speed.y = 0;
	}
	if (speed.y > 0)
	{
		newDirection = eDirection::DIRECTION_DOWN;
	}
	else if (speed.y < 0)
	{
		newDirection = eDirection::DIRECTION_UP;
	}
	actor->setPosition(offset);
	actor->setDirection(newDirection);
}