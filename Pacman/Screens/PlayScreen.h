#ifndef PLAY_SCREEN_H
#define PLAY_SCREEN_H

#include"Screen.h"
#include"../Map/PacmanMap.h"
#include"../Actors/Pacman.h"
#include"../Objects/GameObject.h"
#include"../Actors/Ghost.h"

class PlayScreen : public Screen, public std::enable_shared_from_this<PlayScreen>
{
private:
	std::shared_ptr<PacmanMap> map{ nullptr };
	std::shared_ptr<Pacman> pacman;
	std::vector<std::shared_ptr<Ghost>> ghosts;
	std::vector<std::shared_ptr<GameObject>> pacOnlyInteractable;
	std::vector<std::shared_ptr<GameObject>> allInteractable;
	Image high;
	Image scr;
	Image name;
	Image lives;
	Image hScore;
	Image cScore;
	Image lifeImg;
	int extraLifeCounter{ 0 };
public:
	PlayScreen(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Font> font, std::shared_ptr<Screen> previous)
		: Screen(renderer, font, previous)	{}
	~PlayScreen() {}
	void init() override;
	void render() override;
	std::shared_ptr<Screen> update() override;
	std::shared_ptr<Screen> handleEvents(SDL_Event event) override;
};

#endif