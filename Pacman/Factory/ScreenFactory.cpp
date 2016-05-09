#include"ScreenFactory.h"
#include"../Screens/OptionsScreen.h"
#include"../Screens/MainScreen.h"
#include"../Screens/ScoresScreen.h"
#include"../Screens/PlayScreen.h"
#include"../Screens/PauseScreen.h"
#include"../Screens/DiedScreen.h"
#include"../Screens/TransitionScreen.h"
#include"../Screens/GameOverScreen.h"

std::shared_ptr<Screen> ScreenFactory::makeScreen(eScreen screen, std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous)
{
	if (screen == eScreen::MAIN_SCREEN_ENUM)
	{
		std::shared_ptr<MainScreen> ms = std::make_shared<MainScreen>(renderer, font, previous);
		ms->init();
		return ms;
	}
	else if (screen == eScreen::OPTIONS_SCREEN_ENUM)
	{
		std::shared_ptr<OptionsScreen> os = std::make_shared<OptionsScreen>(renderer, font, previous);
		os->init();
		return os;
	}
	else if (screen == eScreen::HIGHSCORE_SCREEN_ENUM)
	{
		std::shared_ptr<ScoresScreen> ss = std::make_shared<ScoresScreen>(renderer, font, previous);
		ss->init();
		return ss;
	}
	else if (screen == eScreen::PLAY_SCREEN_ENUM)
	{
		std::shared_ptr<PlayScreen> ps = std::make_shared<PlayScreen>(renderer, font, previous);
		ps->init();
		return ps;
	}
	else if (screen == eScreen::PAUSE_SCREEN_ENUM)
	{
		std::shared_ptr<PauseScreen> ps = std::make_shared<PauseScreen>(renderer, font, previous);
		ps->init();
		return ps;
	}
	else
	{
		return nullptr;
	}
}
std::shared_ptr<Screen> ScreenFactory::makeDiedScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, unsigned int delay, eGhost ghostKilled, std::shared_ptr<Screen> previous)
{
	std::shared_ptr<DiedScreen> ds = std::make_shared<DiedScreen>(renderer, font, previous, delay, ghostKilled);
	ds->init();
	return ds;
}
std::shared_ptr<Screen> ScreenFactory::makeTransitionScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, unsigned int delay, int nextLevel, std::shared_ptr<Screen> previous)
{
	std::shared_ptr<TransitionScreen> ts = std::make_shared<TransitionScreen>(renderer, font, previous, delay, nextLevel);
	ts->init();
	return ts;
}
std::shared_ptr<Screen> ScreenFactory::makeGameOverScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, int score, std::shared_ptr<Screen> previous)
{
	std::shared_ptr<GameOverScreen> gs = std::make_shared<GameOverScreen>(renderer, font, previous, score);
	gs->init();
	return gs;
}