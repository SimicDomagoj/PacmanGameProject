#include"PacmanInput.h"
#include"../Service/Options.h"
#include"../Consts/Constants.h"

void PacmanInput::handleInput(std::shared_ptr<Actor> actor, SDL_Event event)
{
	SDL_Point speed = actor->getSpeed();

	if (Options::get().getValue("keybindings") == "keys")
	{
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_UP: speed.y -= Constants::speed; break;
			case SDLK_DOWN: speed.y += Constants::speed; break;
			case SDLK_RIGHT: speed.x += Constants::speed; break;
			case SDLK_LEFT: speed.x -= Constants::speed; break;
			}
		}
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_UP: speed.y = 0; break;
			case SDLK_DOWN: speed.y = 0; break;
			case SDLK_RIGHT: speed.x = 0; break;
			case SDLK_LEFT: speed.x = 0; break;
			}
		}
	}
	else
	{
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_w: speed.y = 0; break;
			case SDLK_s: speed.y = 0; break;
			case SDLK_d: speed.x = 0; break;
			case SDLK_a: speed.x = 0; break;
			}
		}
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_w: speed.y += Constants::speed; break;
			case SDLK_s: speed.y -= Constants::speed; break;
			case SDLK_d: speed.x -= Constants::speed; break;
			case SDLK_a: speed.x += Constants::speed; break;
			}
		}
	}
	actor->setSpeed(speed);
}