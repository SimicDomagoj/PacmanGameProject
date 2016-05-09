#include "Screen.h"
#ifndef OPTIONS_SCREEN_H
#define OPTIONS_SCREEN_H

class OptionsScreen : public Screen
{
private:
	Image back;
	Image on;
	Image off;
	Image keys;
	Image arrows;
	Image windowed;
	Image fullScreen;
	Image slash;
	Image sound;
	Image keybindings;
	Image windowSize;
public:
	OptionsScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous = nullptr)
		: Screen(renderer, font, previous){}
	~OptionsScreen() {}
	void init() override;
	void render() override;
	std::shared_ptr<Screen> update() override;
	std::shared_ptr<Screen> handleEvents(SDL_Event event) override;
};

#endif