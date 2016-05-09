#include"GhostAI.h"
#include"../Actors/Ghost.h"

void GhostAI::HandleAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map)
{
	SDL_Rect position = ghost->getPosition();	
	if (powerdownTime.get_ticks() > Constants::powerdownDuration)
	{
		turnNormal(ghost);
	}
	eState state = ghost->getState();
	if ((position.x - Constants::mapStartXPos) % Constants::tileWidth == 0 && (position.y - Constants::mapStartYPos) % Constants::tileHeight == 0)
	{
		switch (state)
		{
		case eState::GHOST_DEAD: deadAI(ghost, map); break;
		case eState::GHOST_NORMAL: normalAI(ghost, map); break;
		case eState::GHOST_POWERDOWN: powerdownAI(ghost, map); break;
		default: break;
		}
	}
}
unsigned int GhostAI::getScatterDuration(int level)
{
	if (level == 1)
	{
		if (timesModeSwitched <= 1)
		{
			return 7;
		}
		else if (timesModeSwitched <= 3)
		{
			return 5;
		}
	}
	else if (level <= 5)
	{
		if (timesModeSwitched <= 1)
		{
			return 7;
		}
		else if (timesModeSwitched < 3)
		{
			return 5;
		}
	}
	else
	{
		if (timesModeSwitched <= 2)
		{
			return 5;
		}
	}
	return 0;
}
eDirection GhostAI::findPath(std::shared_ptr<Ghost> ghost, SDL_Point finish, std::shared_ptr<PacmanMap> map)
{
	SDL_Rect start = ghost->getPosition();
	eDirection currentDirection = ghost->getDirection(), newDirection;
	int x = (start.x - Constants::mapStartXPos) / Constants::tileWidth, y = (start.y - Constants::mapStartYPos) / Constants::tileHeight;
	int x2 = finish.x, y2 = finish.y;

	float up = 1000, down = 1000, left = 1000, right = 1000, min;
	if ((x + 1) < 15 && map->getAtXY(x + 1, y) != FieldType::WALL && map->getAtXY(x + 1, y) != FieldType::CAGE && currentDirection != eDirection::DIRECTION_LEFT)
	{
		right = sqrt(pow((float)x2 - (x + 1), 2) + pow((float)y2 - y, 2));
	}
	if ((x - 1) >= 0 && map->getAtXY(x - 1, y) != FieldType::WALL && map->getAtXY(x - 1, y) != FieldType::CAGE && currentDirection != eDirection::DIRECTION_RIGHT)
	{
		left = sqrt(pow((float)x2 - (x - 1), 2) + pow((float)y2 - y, 2));
	}
	if ((y + 1)<17 && map->getAtXY(x, y + 1) != FieldType::WALL && map->getAtXY(x, y + 1) != FieldType::CAGE && map->getAtXY(x, y + 1) != FieldType::CAGE_ENTRANCE && currentDirection != eDirection::DIRECTION_UP)
	{
		down = sqrt(pow((float)x2 - x, 2) + pow((float)y2 - (y + 1), 2));
	}
	if ((y - 1) >= 0 && map->getAtXY(x, y - 1) != FieldType::WALL && map->getAtXY(x, y - 1) != FieldType::CAGE && map->getAtXY(x, y) != FieldType::PACMAN_ONLY_CROSSROAD && currentDirection != eDirection::DIRECTION_DOWN)
	{
		up = sqrt(pow((float)x2 - x, 2) + pow((float)y2 - (y - 1), 2));
	}
	min = up;
	newDirection = eDirection::DIRECTION_UP;
	if (right<min)
	{
		min = right;
		newDirection = eDirection::DIRECTION_RIGHT;
	}
	if (left<min)
	{
		min = left;
		newDirection = eDirection::DIRECTION_LEFT;
	}
	if (down<min)
	{
		min = down;
		newDirection = eDirection::DIRECTION_DOWN;
	}
	return newDirection;
}
void GhostAI::deadAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map)
{
	SDL_Rect position = ghost->getPosition();
	int xStart = (position.x - Constants::mapStartXPos) / Constants::tileWidth;
	int yStart = (position.y - Constants::mapStartYPos) / Constants::tileHeight;
	eDirection direction;

	if (xStart != 7 || yStart != 6)
	{
		direction = findPath(ghost, SDL_Point{ 7, 6 }, map);
	}
	else if (xStart == 7 && yStart == 6)
	{
		direction = eDirection::DIRECTION_DOWN;
	}
	if (xStart == 7 && yStart == 7)
	{
		ghost->turnNormal();
		direction = eDirection::DIRECTION_UP;
	}
	ghost->setDirection(direction);
}

void GhostAI::powerdownAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map)
{
	SDL_Rect position = ghost->getPosition();
	int xStart = (position.x - Constants::mapStartXPos) / Constants::tileWidth;
	int yStart = (position.y - Constants::mapStartYPos) / Constants::tileHeight;
	eDirection direction = ghost->getDirection();

	if ((map->getAtXY(xStart, yStart) == FieldType::CROSSROAD || map->getAtXY(xStart, yStart) == FieldType::PACMAN_ONLY_CROSSROAD))
	{
		while (1)
		{
			direction = static_cast<eDirection>(rand() % 4);
			if (direction == eDirection::DIRECTION_RIGHT && map->getAtXY(xStart + 1, yStart) != FieldType::WALL && map->getAtXY(xStart + 1, yStart) != FieldType::CAGE && map->getAtXY(xStart + 1, yStart) != FieldType::CAGE_ENTRANCE && xStart + 1<15)
			{
				break;
			}
			else if (direction == eDirection::DIRECTION_DOWN && map->getAtXY(xStart, yStart + 1) != FieldType::WALL && map->getAtXY(xStart, yStart + 1) != FieldType::CAGE && map->getAtXY(xStart, yStart + 1) != FieldType::CAGE_ENTRANCE && yStart + 1<17)
			{
				break;
			}
			else if (direction == eDirection::DIRECTION_LEFT && map->getAtXY(xStart - 1, yStart) != FieldType::WALL && map->getAtXY(xStart - 1, yStart) != FieldType::CAGE && map->getAtXY(xStart - 1, yStart) != FieldType::CAGE_ENTRANCE && xStart - 1>0)
			{
				break;
			}
			else if (direction == eDirection::DIRECTION_UP && map->getAtXY(xStart, yStart - 1) != FieldType::WALL && map->getAtXY(xStart, yStart - 1) != FieldType::CAGE && map->getAtXY(xStart + 1, yStart - 1) != FieldType::CAGE_ENTRANCE && yStart - 1>0)
			{
				break;
			}
		}
	}
	else if (map->getAtXY(xStart, yStart) == FieldType::CORNER)
	{
		if (direction == eDirection::DIRECTION_RIGHT || direction == eDirection::DIRECTION_LEFT)
		{
			if (yStart == 0 || map->getAtXY(xStart, yStart - 1) == FieldType::WALL)
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
			if (xStart == 0 || map->getAtXY(xStart - 1, yStart) == FieldType::WALL)
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

void GhostAI::die(std::shared_ptr<Ghost> ghost)
{
	if (ghost->getState() == eState::GHOST_POWERDOWN)
	{
		powerdownTime.stop();
		timesModeSwitched = 0;
		ghost->setState(eState::GHOST_DEAD);
	}
}
void GhostAI::powerdown(std::shared_ptr<Ghost> ghost)
{
	if (ghost->getState() == eState::GHOST_NORMAL)
	{
		powerdownTime.start();
		destinationSwitch.pause();
		ghost->setState(eState::GHOST_POWERDOWN);
	}
}

void GhostAI::turnNormal(std::shared_ptr<Ghost> ghost)
{
	if (ghost->getState() == eState::GHOST_POWERDOWN)
	{
		powerdownTime.stop();
		destinationSwitch.unpause();
		ghost->setState(eState::GHOST_NORMAL);
	}
	else
	{
		destinationSwitch.start();
		ghost->setState(eState::GHOST_NORMAL);
	}
}