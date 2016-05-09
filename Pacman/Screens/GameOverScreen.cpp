#include"GameOverScreen.h"
#include"../Service/ScoresHandler.h"
#include"../Consts/Constants.h"

GameOverScreen::GameOverScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous, int score)
	: score{score}, Screen(renderer, font, previous)
{
	delayTimer.start();
	position = ScoresHandler::get().checkPosition(score);
}

void GameOverScreen::init()
{
	Uint8 white[3] = { 0, 0, 0 };
	background.load_image(Constants::backgroundImageLoc, renderer);
	gameover.loadFromText("game over", font->getFont(60), SDL_Color{ 0, 0, 0 }, renderer);
	congrats.loadFromText("congratulations", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	yourScore.loadFromText("your score: " + std::to_string(score), font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	enterName.loadFromText("enter your name: ", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
}
void GameOverScreen::render()
{
	background.apply_surface(renderer, 0, 0);
	if (!showSecond)
	{
		gameover.apply_surface(renderer, (Constants::screenWidth - gameover.getWidth()) / 2, (Constants::screenHeight - gameover.getHeight()) / 2);
	}
	else
	{
		if (position > 0)
		{
			congrats.apply_surface(renderer, (Constants::screenWidth - gameover.getWidth()) / 2, 320);
		}
		yourScore.apply_surface(renderer, (Constants::screenWidth - gameover.getWidth()) / 2, 360);
		enterName.apply_surface(renderer, (Constants::screenWidth - gameover.getWidth()) / 2, 400);
		if (name != "")
		{
			nameImg.apply_surface(renderer, (Constants::screenWidth - gameover.getWidth()) / 2, 440);
		}
	}
}
std::shared_ptr<Screen> GameOverScreen::update()
{
	if (delayTimer.is_started() && delayTimer.get_ticks() > 1500)
	{
		delayTimer.stop();
		showSecond = true;
	}
	return nullptr;
}
std::shared_ptr<Screen> GameOverScreen::handleEvents(SDL_Event event)
{
	if (showSecond)
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_BACKSPACE && name.length() > 0)
			{
				name.pop_back();
				nameImg.loadFromText(name, font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
			}
			else if (event.key.keysym.sym == SDLK_RETURN)
			{
				if (name == "")
				{
					name = "unknown";
				}
				ScoresHandler::get().recordNewScore(name, score);
				ScoresHandler::get().save(std::ofstream{ Constants::scoresLoc });
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
		else if (event.type == SDL_TEXTINPUT)
		{
			if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
			{
				if (name.length() <= Constants::maxNameLenght)
				{
					name += event.text.text;
					nameImg.loadFromText(name, font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
				}
			}
		}
	}
	return nullptr;
}