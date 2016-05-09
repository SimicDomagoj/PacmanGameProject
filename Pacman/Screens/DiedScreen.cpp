#include"DiedScreen.h"

DiedScreen::DiedScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous, unsigned int delay, eGhost ghostKilled)
	: delayMiliseconds{ delay }, Screen(renderer, font, previous)
{
	delayTimer.start();
	switch (ghostKilled)
	{
	case eGhost::BLINKY:
		showArea = std::make_shared<SDL_Rect>(SDL_Rect{ 200, 0, 200, 200 });
		break;
	case eGhost::PINKY:
		showArea = std::make_shared<SDL_Rect>(SDL_Rect{ 200, 210, 200, 200 });
		break;
	case eGhost::INKY:
		showArea = std::make_shared<SDL_Rect>(SDL_Rect{ 0, 210, 200, 200 });
		break;
	case eGhost::CLYDE:
		showArea = std::make_shared<SDL_Rect>(SDL_Rect{ 0, 0, 200, 200 });
		break;
	default:
		break;
	}
}

void DiedScreen::init()
{
	Uint8 white[3] = { 0, 0, 0 };
	background.load_image(Constants::backgroundImageLoc, renderer);
	ghostImage.load_image(Constants::cuteGhostsImageLoc, renderer, white);
}
void DiedScreen::render()
{
	background.apply_surface(renderer, 0, 0);
	ghostImage.apply_surface(renderer, (Constants::screenWidth - showArea->w) / 2, (Constants::screenHeight - showArea->h) / 2, showArea);
}
std::shared_ptr<Screen> DiedScreen::update()
{
	if (delayTimer.get_ticks() > delayMiliseconds)
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
	return nullptr;
}
std::shared_ptr<Screen> DiedScreen::handleEvents(SDL_Event event)
{	
	return nullptr;
}