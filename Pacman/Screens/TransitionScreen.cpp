#include"TransitionScreen.h"
#include"../Consts/Constants.h"

TransitionScreen::TransitionScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous, unsigned int delay, int nextLevel)
	: delayMiliseconds{ delay }, nextLevel{ nextLevel }, Screen(renderer, font, previous){}

void TransitionScreen::init()
{
	Uint8 white[3] = { 0, 0, 0 };
	background.load_image(Constants::transitionImageLoc, renderer);
	level.loadFromText("level" + std::to_string(nextLevel), font->getFont(60), SDL_Color{ 0, 0, 0 }, renderer);
}
void TransitionScreen::render()
{
	background.apply_surface(renderer, 0, 0);
	level.apply_surface(renderer, imagePos.x, imagePos.y);
}
std::shared_ptr<Screen> TransitionScreen::update()
{
	if (imagePos.x < 400)
	{
		imagePos.x += 5;
	}
	else if (!delayTimer.is_started())
	{
		delayTimer.start();
	}
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
std::shared_ptr<Screen> TransitionScreen::handleEvents(SDL_Event event)
{
	return nullptr;
}