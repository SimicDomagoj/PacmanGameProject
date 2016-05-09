#include"MainScreen.h"
#include"../Timer\Timer.h"
#include"../Service/CollisionService.h"
#include"../Factory/ScreenFactory.h"

void MainScreen::init()
{
	background.load_image("Resources/bg1.png", renderer);
	game.loadFromText("new game", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	options.loadFromText("options", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	hall.loadFromText("hall of fame", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	quit.loadFromText("quit", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
}

void MainScreen::render()
{
	background.apply_surface(renderer, 0, 0);
	game.apply_surface(renderer, (Constants::screenWidth - game.getWidth()) / 2, 200);
	options.apply_surface(renderer, (Constants::screenWidth - options.getWidth()) / 2, 250);
	hall.apply_surface(renderer, (Constants::screenWidth - hall.getWidth()) / 2, 300);
	quit.apply_surface(renderer, (Constants::screenWidth - quit.getWidth()) / 2, 350);
}

std::shared_ptr<Screen> MainScreen::update()
{
	return nullptr;
}

std::shared_ptr<Screen> MainScreen::handleEvents(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (CollisionService::checkCollision(quit.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				SDL_Event sdlevent;
				sdlevent.type = SDL_QUIT;
				sdlevent.key.keysym.sym = SDLK_1;
				SDL_PushEvent(&sdlevent);
			}
			else if (CollisionService::checkCollision(hall.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				return ScreenFactory::makeScreen(eScreen::HIGHSCORE_SCREEN_ENUM, renderer, font, shared_from_this());
			}
			else if (CollisionService::checkCollision(options.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				return ScreenFactory::makeScreen(eScreen::OPTIONS_SCREEN_ENUM, renderer, font, shared_from_this());
			}
			else if (CollisionService::checkCollision(game.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				return ScreenFactory::makeScreen(eScreen::PLAY_SCREEN_ENUM, renderer, font, shared_from_this());
			}
		}
	}
	return nullptr;
}