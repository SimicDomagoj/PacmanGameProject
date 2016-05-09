#ifndef TRANSITION_SCREEN_H
#define TRANSITION_SCREEN_H

#include"Screen.h"
#include"../Timer/Timer.h"

class TransitionScreen : public Screen
{
private:
	Image level;
	Timer delayTimer;
	unsigned int delayMiliseconds;
	int nextLevel;
	SDL_Point imagePos = SDL_Point{ -140, 450 };
public:
	TransitionScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous, unsigned int delay, int nextLevel);
	~TransitionScreen() {}
	void init() override;
	void render() override;
	std::shared_ptr<Screen> update() override;
	std::shared_ptr<Screen> handleEvents(SDL_Event event) override;
};

#endif