#include"PacmanGraphics.h"
#include"../Consts/Constants.h"

void PacmanGraphics::Render(std::shared_ptr<Actor> actor, std::shared_ptr<SDL_Renderer> renderer)
{
	SDL_Rect clip{ 0, 0, Constants::tileWidth, Constants::tileHeight };
	clip.x = frame * Constants::tileWidth;
	eDirection direction = actor->getDirection();
	SDL_Rect position = actor->getPosition();
	switch (direction)
	{
		case eDirection::DIRECTION_UP: 
			clip.y = Constants::tileHeight;
			break;
		case eDirection::DIRECTION_DOWN:
			clip.y = 3 * Constants::tileHeight;
			break;
		case eDirection::DIRECTION_LEFT:
			clip.y = 2 * Constants::tileHeight;
			break;
		case eDirection::DIRECTION_RIGHT:
			clip.y = 0;
			break;
		default:
			break;
	}
	if (frame == 2) clip.y = 0;

	bitmap.apply_surface(renderer, position.x, position.y, std::make_shared<SDL_Rect>(clip));
	int time = showNext.get_ticks();
	if (showNext.get_ticks() > 75)
	{
		if (++frame > 2)
		{
			frame = 0;
		}
		showNext.start();
	}
}