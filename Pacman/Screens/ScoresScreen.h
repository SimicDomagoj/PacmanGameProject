#include"Screen.h"
#include<vector>
#ifndef SCORES_SCREEN_H
#define SCORES_SCREEN_H

class ScoresScreen : public Screen
{
private:
	Image back;
	Image hallOfFame;
	std::vector<Image> scores{ 10 };
public:
	ScoresScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous)
		:Screen(renderer, font, previous){	}
	~ScoresScreen() {};
	void init() override;
	void render() override;
	std::shared_ptr<Screen> update() override;
	std::shared_ptr<Screen> handleEvents(SDL_Event event) override;
};

#endif