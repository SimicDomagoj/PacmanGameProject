#ifndef DIED_SCREEN_H
#define DIED_SCREEN_H

#include"Screen.h"
#include"../Timer/Timer.h"
#include"../Actors/Ghost.h"

class DiedScreen : public Screen
{
private:	
	Image ghostImage;
	Timer delayTimer;
	unsigned int delayMiliseconds;
	std::shared_ptr<SDL_Rect> showArea;
public:
	DiedScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous, unsigned int delay, eGhost ghostKilled);
	~DiedScreen() {}
	void init() override;
	void render() override;
	std::shared_ptr<Screen> update() override;
	std::shared_ptr<Screen> handleEvents(SDL_Event event) override;
};

#endif