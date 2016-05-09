#ifndef SCREEN_FACTORY_H
#define SCREEN_FACTORY_H

#include"../Screens/Screen.h"
#include<memory>
#include<SDL.h>
#include"../Service/Font.h"
#include"../Actors/Ghost.h"

class ScreenFactory
{
public:
	static std::shared_ptr<Screen> makeScreen(eScreen screen, std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous = nullptr);
	static std::shared_ptr<Screen> makeDiedScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, unsigned int delay, eGhost ghostKilled, std::shared_ptr<Screen> previous = nullptr);
	static std::shared_ptr<Screen> makeTransitionScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, unsigned int delay, int nextLevel, std::shared_ptr<Screen> previous = nullptr);
	static std::shared_ptr<Screen> makeGameOverScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, int score, std::shared_ptr<Screen> previous = nullptr);
};

#endif