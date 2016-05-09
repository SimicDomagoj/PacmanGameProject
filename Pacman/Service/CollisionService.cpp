#include"CollisionService.h"

bool CollisionService::checkCollision(SDL_Rect A, SDL_Rect B)
{
	int leftA = A.x;
	int topA = A.y;
	int bottomA = A.y + A.h;
	int rightA = A.x + A.w;
	int leftB = B.x;
	int topB = B.y;
	int bottomB = B.y + B.h;
	int rightB = B.x + B.w;

	if (bottomA <= topB)
	{
		return false;
	}
	if (topA >= bottomB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	return true;
}

bool CollisionService::checkCollision(SDL_Rect r, SDL_Point p)
{
	int leftA = r.x;
	int topA = r.y;
	int bottomA = r.y + r.h;
	int rightA = r.x + r.w;

	if (bottomA <= p.y)
	{
		return false;
	}
	if (topA >= p.y)
	{
		return false;
	}
	if (leftA >= p.x)
	{
		return false;
	}
	if (rightA <= p.x)
	{
		return false;
	}
	return true;
}

bool CollisionService::checkCollision(std::shared_ptr<Actor> actor, std::shared_ptr<PacmanMap> map)
{
	std::vector<field> fields = map->getFields();
	std::vector<field> boundaries = map->getBoundaries();
	SDL_Rect rect = actor->getPosition();
	for (unsigned int i = 0; i < fields.size(); i++)
	{
		if (fields[i].type == FieldType::WALL && checkCollision(rect, fields[i].area))
		{
			return true;
		}
	}
	for (unsigned int i = 0; i < boundaries.size(); i++)
	{
		if ((boundaries[i].type == FieldType::WALL || boundaries[i].type == FieldType::DOOR) && checkCollision(rect, boundaries[i].area))
		{
			return true;
		}
	}
	return false;
}

bool CollisionService::checkCollision(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map)
{
	std::vector<field> fields = map->getFields();
	std::vector<field> boundaries = map->getBoundaries();
	SDL_Rect rect = ghost->getPosition();
	if (ghost->getState() != eState::GHOST_POWERDOWN)
	{
		rect.x += 3; rect.y += 3;
		rect.w -= 6; rect.h -= 6;
	}
	for (unsigned int i = 0; i < fields.size(); i++)
	{
		if (fields[i].type == FieldType::WALL && checkCollision(rect, fields[i].area))
		{
			return true;
		}
	}
	for (unsigned int i = 0; i < boundaries.size(); i++)
	{
		if ((boundaries[i].type == FieldType::WALL) && checkCollision(rect, boundaries[i].area))
		{
			return true;
		}
	}
	return false;
}

bool CollisionService::checkCollision(std::shared_ptr<Actor> actor, std::shared_ptr<Ghost> ghost)
{
	SDL_Rect rect = actor->getPosition(), rect2 = ghost->getPosition();
	rect.x += 4; rect.y += 4; rect.w -= 8; rect.h -= 8;
	rect2.x += 4; rect2.y += 4; rect2.w -= 8; rect2.h -= 8;
	if (checkCollision(rect, rect2))
	{
		return true;
	}
	return false;
}