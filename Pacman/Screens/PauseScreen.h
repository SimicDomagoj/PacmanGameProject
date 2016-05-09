#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include"Screen.h"

class PauseScreen : public Screen
{
private:
	Image pause;
public:
	PauseScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous)
		: Screen(renderer, font, previous)
	{}
	~PauseScreen() {}
	void init() override;
	void render() override;
	std::shared_ptr<Screen> update() override;
	std::shared_ptr<Screen> handleEvents(SDL_Event event) override;
};

#endif