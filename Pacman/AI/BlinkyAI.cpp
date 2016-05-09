#include"GhostAI.h"
#include"../Actors/Ghost.h"

void BlinkyAI::normalAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map)
{
	SDL_Rect destPosition = toFollow->getPosition(), position = ghost->getPosition();
	eDirection direction = ghost->getDirection();
	int level = ghost->getLevel();

	unsigned int scatterTime = getScatterDuration(level);
	SDL_Point start = SDL_Point{ (position.x - Constants::mapStartXPos) / Constants::tileWidth, (position.y - Constants::mapStartYPos) / Constants::tileHeight };
	SDL_Point finish = SDL_Point{ (destPosition.x - Constants::mapStartXPos) / Constants::tileWidth, (destPosition.y - Constants::mapStartYPos) / Constants::tileHeight };

	if (start.x == 7 && start.y == 7)
	{
		direction = eDirection::DIRECTION_UP;
	}
	else if (map->getAtXY(start.x, start.y) == FieldType::CROSSROAD || map->getAtXY(start.x, start.y) == FieldType::PACMAN_ONLY_CROSSROAD)
	{
		if (destinationSwitch.get_ticks() / 1000 <= scatterTime && level < Constants::breakPointLevel)
		{
			direction = findPath(ghost, homeTile, map);
		}
		else if (destinationSwitch.get_ticks() / 1000 <= Constants::minScatterTime + scatterTime || level >= Constants::breakPointLevel)
		{
			direction = findPath(ghost, finish, map);
		}
		else if (level < Constants::breakPointLevel)
		{
			destinationSwitch.start();
			timesModeSwitched++;
			switch (direction)
			{
				case eDirection::DIRECTION_DOWN: direction = eDirection::DIRECTION_UP; break;
				case eDirection::DIRECTION_UP: direction = eDirection::DIRECTION_DOWN; break;
				case eDirection::DIRECTION_LEFT: direction = eDirection::DIRECTION_RIGHT; break;
				case eDirection::DIRECTION_RIGHT: direction = eDirection::DIRECTION_LEFT; break;
				default: break;
			}
		}
	}
	else if (map->getAtXY(start.x, start.y) == FieldType::CORNER)
	{
		if (direction == eDirection::DIRECTION_RIGHT || direction == eDirection::DIRECTION_LEFT)
		{
			if (start.y == 0 || map->getAtXY(start.x, start.y - 1) == FieldType::WALL)
			{
				direction = eDirection::DIRECTION_DOWN;
			}
			else
			{
				direction = eDirection::DIRECTION_UP;
			}
		}
		else if (direction == eDirection::DIRECTION_DOWN || direction == eDirection::DIRECTION_UP)
		{
			if (start.x == 0 || map->getAtXY(start.x - 1, start.y) == FieldType::WALL)
			{
				direction = eDirection::DIRECTION_RIGHT;
			}
			else
			{
				direction = eDirection::DIRECTION_LEFT;
			}
		}
	}
	ghost->setDirection(direction);
}