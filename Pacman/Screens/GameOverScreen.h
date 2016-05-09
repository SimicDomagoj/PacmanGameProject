#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include"Screen.h"
#include"../Timer/Timer.h"

class GameOverScreen : public Screen
{
private:
	Image gameover;
	Image congrats;
	Image yourScore;
	Image enterName;
	Image nameImg;
	int score;
	int position;
	bool showSecond{ false };
	std::string name{ "" };
	Timer delayTimer;
public:
	GameOverScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous, int score);
	~GameOverScreen() {}
	void init() override;
	void render() override;
	std::shared_ptr<Screen> update() override;
	std::shared_ptr<Screen> handleEvents(SDL_Event event) override;
};

#endif