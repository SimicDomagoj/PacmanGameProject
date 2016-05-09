#include"../Image/Image.h"
#include"../Service/Font.h"

#ifndef SCREEN_H
#define SCREEN_H

enum class eScreen { MAIN_SCREEN_ENUM, OPTIONS_SCREEN_ENUM, HIGHSCORE_SCREEN_ENUM, PLAY_SCREEN_ENUM, PAUSE_SCREEN_ENUM, DIED_SCREEN_ENUM, TRANSITION_SCREEN_ENUM, GAME_OVER_SCREEN_ENUM };

class Screen
{
protected:
	std::shared_ptr<Screen> previousScreen{ nullptr };
	std::shared_ptr<SDL_Renderer> renderer{ nullptr };
	std::shared_ptr<Font> font{ nullptr };
	Image background;

public:
	Screen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous = nullptr)
		: previousScreen{ previous }, font{ font }, renderer{ renderer } {}
	virtual void init() = 0;
	virtual void render() = 0;
	virtual std::shared_ptr<Screen> update() = 0;
	virtual std::shared_ptr<Screen> handleEvents(SDL_Event event) = 0;
	std::shared_ptr<SDL_Renderer> getRenderer() { return renderer; }
	void setRenderer(std::shared_ptr<SDL_Renderer> r) { renderer = r; }
	std::shared_ptr<Font> getFont() { return font; }
	void setFont(std::shared_ptr<Font> f) { font = f; }
	virtual ~Screen() { font.reset(); }
};



#endif