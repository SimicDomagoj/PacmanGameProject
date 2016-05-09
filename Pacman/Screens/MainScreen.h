#include "Screen.h"
#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

class MainScreen : public Screen, public std::enable_shared_from_this<MainScreen>
{
private:
	Image game;
	Image options;
	Image hall;
	Image quit;
public:
	MainScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous = nullptr)
		:Screen(renderer, font, previous){	}
	~MainScreen() {}
	void init() override;
	void render() override;
	std::shared_ptr<Screen> update() override;
	std::shared_ptr<Screen> handleEvents(SDL_Event event) override;
};

#endif