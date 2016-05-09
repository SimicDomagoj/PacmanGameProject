#include"PauseScreen.h"
#include"../Consts/Constants.h"

void PauseScreen::init()
{
	background.load_image(Constants::backgroundImageLoc, renderer);
	pause.loadFromText("paused", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
}
void PauseScreen::render()
{
	background.apply_surface(renderer, 0, 0);
	pause.apply_surface(renderer, (Constants::screenWidth - pause.getWidth()) / 2, (Constants::screenHeight -pause.getHeight()) / 2);
}
std::shared_ptr<Screen> PauseScreen::update()
{
	return nullptr;
}
std::shared_ptr<Screen> PauseScreen::handleEvents(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_p)
		{
			if (previousScreen == nullptr)
			{
				SDL_Event sdlevent;
				sdlevent.type = SDL_QUIT;
				sdlevent.key.keysym.sym = SDLK_1;
				SDL_PushEvent(&sdlevent);
			}
			return previousScreen;
		}
	}
	return nullptr;
}