#include"GhostGraphics.h"
#include"../Actors/Ghost.h"

void GhostGraphics::Render(std::shared_ptr<Ghost> actor, std::shared_ptr<SDL_Renderer> renderer)
{
	SDL_Rect clip{ 0, 0, Constants::tileWidth, Constants::tileHeight };
	SDL_Rect position = actor->getPosition();
	eState state = actor->getState();
	switch (actor->getDirection())
	{
	case eDirection::DIRECTION_DOWN: clip.x = Constants::tileWidth; break;
	case eDirection::DIRECTION_RIGHT: clip.x = 2 * Constants::tileWidth; break;
	case eDirection::DIRECTION_LEFT: clip.x = 3 * Constants::tileWidth; break;
		default:
			break;
	}
	if (state == eState::GHOST_DEAD)
	{
		clip.y = 2 * Constants::tileHeight;
	}
	else if(state == eState::GHOST_NORMAL)
	{
		clip.y = 0;
	}
	else if (state == eState::GHOST_POWERDOWN)
	{
		clip.y = Constants::tileHeight;
		int i = SDL_GetTicks() / 1000;
		if (i % 2 == 0)
		{
			clip.x = 0;
		}
		else
		{
			clip.x = Constants::tileWidth;
		}
	}
	bitmap.apply_surface(renderer, position.x, position.y, std::make_shared<SDL_Rect>(clip));
}