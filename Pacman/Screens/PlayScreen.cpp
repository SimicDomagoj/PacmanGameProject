#include"PlayScreen.h"
#include"../Factory/GameObjectFactory.h"
#include"../Factory/PacmanFactory.h"
#include"../Factory/GhostFactory.h"
#include"../Service/ScoresHandler.h"
#include"../Service/CollisionService.h"
#include"../Factory/ScreenFactory.h"

void PlayScreen::init()
{
	map = std::make_shared<PacmanMap>(Constants::mapLoc);
	Uint8 blueish[3] = { 0, 255, 255 };
	std::vector<std::shared_ptr<IObserver>> obs;

	pacman = PacmanFactory::getPacman(map->getPacmanStartPos(), renderer, Constants::pacmanImageLoc, blueish);
	ghosts.push_back(GhostFactory::getGhost(eGhost::BLINKY, map->getGhostStartPos(eGhost::BLINKY), renderer, pacman));
	ghosts.push_back(GhostFactory::getGhost(eGhost::PINKY, map->getGhostStartPos(eGhost::PINKY), renderer, pacman));
	ghosts.push_back(GhostFactory::getGhost(eGhost::INKY, map->getGhostStartPos(eGhost::INKY), renderer, pacman, ghosts[0]));
	ghosts.push_back(GhostFactory::getGhost(eGhost::CLYDE, map->getGhostStartPos(eGhost::CLYDE), renderer, pacman));
	obs.push_back(ghosts[0]); obs.push_back(ghosts[1]); obs.push_back(ghosts[2]); obs.push_back(ghosts[3]);

	pacOnlyInteractable = GameObjectFactory::getDots(map->getDots(), renderer);
	std::vector<std::shared_ptr<GameObject>> temp = GameObjectFactory::getPowerUps(map->getPowerUps(), renderer, obs);
	pacOnlyInteractable.insert(pacOnlyInteractable.end(), temp.begin(), temp.end());
	std::vector<SDL_Rect> start;
	std::vector<SDL_Point> end;
	start.push_back(SDL_Rect{ 770, 300, 40, 40 }); start.push_back(SDL_Rect{ 120, 300, 40, 40 });
	end.push_back(SDL_Point{ 165, 300 }); end.push_back(SDL_Point{ 725, 300 });
	allInteractable = GameObjectFactory::getTeleporter(start, end, renderer);

	high.loadFromText("high", font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	scr.loadFromText("score:", font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	lives.loadFromText("lives:", font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	name.loadFromText(ScoresHandler::get().getScores()[0].first, font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	hScore.loadFromText(std::to_string(ScoresHandler::get().getScores()[0].second), font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	cScore.loadFromText(std::to_string(pacman->getScore()), font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	lifeImg.load_image(Constants::lifeImageLoc, renderer, blueish);
}

void PlayScreen::render()
{
	map->render(renderer);
	for (auto &obj : pacOnlyInteractable)
	{
		obj->HandleGraphics(renderer);
	}
	pacman->HandleGraphics(renderer);
	for (auto &ghost : ghosts)
	{
		ghost->HandleGraphics(renderer);
	}
	high.apply_surface(renderer, (180 - high.getWidth()) / 2 + 780, 140);
	lives.apply_surface(renderer, (180 - lives.getWidth()) / 2, 380);
	scr.apply_surface(renderer, (180 - scr.getWidth()) / 2 + 780, 180);
	scr.apply_surface(renderer, (180 - scr.getWidth()) / 2, 140);
	name.apply_surface(renderer, (180 - name.getWidth()) / 2 + 780, 240);
	hScore.apply_surface(renderer, (180 - hScore.getWidth()) / 2 + 780, 300);
	cScore.apply_surface(renderer, (180 - cScore.getWidth()) / 2, 220);
	for (int i = 0; i < pacman->getLives();  ++i)
	{
		lifeImg.apply_surface(renderer, 70, 440 + i * 40);
	}

}

std::shared_ptr<Screen> PlayScreen::update()
{
	ghosts[0]->HandleAI(map);
	ghosts[1]->HandleAI(map);
	ghosts[2]->HandleAI(map);
	ghosts[3]->HandleAI(map);

	ghosts[0]->HandlePhysics(map); 
	ghosts[1]->HandlePhysics(map); 
	if (pacOnlyInteractable.size() < 246)
	{
		ghosts[2]->HandlePhysics(map);
	}
	if (pacOnlyInteractable.size() < 181)
	{
		ghosts[3]->HandlePhysics(map);
	}
	pacman->HandlePhysics(map);

	for (auto &obj : allInteractable)
	{
		for (auto &ghost : ghosts)
		{
			if (CollisionService::checkCollision(ghost->getPosition(), obj->getPosition()))
			{
				obj->update(ghost);
			}
		}
		if (CollisionService::checkCollision(pacman->getPosition(), obj->getPosition()))
		{
			obj->update(pacman);
		}
	}
	std::vector<std::shared_ptr<GameObject>>::iterator it = pacOnlyInteractable.begin();
	while (it != pacOnlyInteractable.end())
	{
		if (CollisionService::checkCollision(pacman->getPosition(), it->get()->getPosition()))
		{
			it->get()->update(pacman);
			it = pacOnlyInteractable.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto &ghost : ghosts)
	{
		if (CollisionService::checkCollision(pacman, ghost))
		{
			if (ghost->getState() == eState::GHOST_NORMAL)
			{
				pacman->loseLife();
				for (unsigned int i = 0; i < ghosts.size(); ++i)
				{
					ghosts[i]->turnNormal();
					ghosts[i]->setPosition(map->getGhostStartPos(static_cast<eGhost>(i)));
				}
				pacman->setPosition(map->getPacmanStartPos());
				pacman->setSpeed(SDL_Point{ 0, 0 });
				eGhost gh = static_cast<eGhost>(std::find(ghosts.begin(), ghosts.end(), ghost) - ghosts.begin());
				return ScreenFactory::makeDiedScreen(renderer, font, 2000, gh, shared_from_this());
			}
			else if (ghost->getState() == eState::GHOST_POWERDOWN)
			{
				ghost->die();
				pacman->adjustScore(ghost->getScore());
			}
		}
	}
	if (pacman->getLives() < Constants::maxLives && pacman->getScore() > Constants::lifeUpScore * (extraLifeCounter + 1))
	{
		extraLifeCounter++;
		pacman->lifeUp();
	}
	if (pacOnlyInteractable.size() == 0)
	{
		for (unsigned int i = 0; i < ghosts.size(); ++i)
		{
			ghosts[i]->levelUp();
			ghosts[i]->turnNormal();
			ghosts[i]->setPosition(map->getGhostStartPos(static_cast<eGhost>(i)));
		}
		pacOnlyInteractable = GameObjectFactory::getDots(map->getDots(), renderer);
		std::vector<std::shared_ptr<IObserver>> obs;
		obs.push_back(ghosts[0]); obs.push_back(ghosts[1]); obs.push_back(ghosts[2]); obs.push_back(ghosts[3]);
		std::vector<std::shared_ptr<GameObject>> temp = GameObjectFactory::getPowerUps(map->getPowerUps(), renderer, obs);
		pacOnlyInteractable.insert(pacOnlyInteractable.end(), temp.begin(), temp.end());

		pacman->setPosition(map->getPacmanStartPos());
		pacman->setSpeed(SDL_Point{ 0, 0 });

		return ScreenFactory::makeTransitionScreen(renderer, font, 2000, ghosts[0]->getLevel(), shared_from_this());
	}
	if (pacman->getLives() <= 0)
	{
		return ScreenFactory::makeGameOverScreen(renderer, font, pacman->getScore(), previousScreen);
	}

	cScore.loadFromText(std::to_string(pacman->getScore()), font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);

	return nullptr;
}

std::shared_ptr<Screen> PlayScreen::handleEvents(SDL_Event event)
{	
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_p)
		{
			return ScreenFactory::makeScreen(eScreen::PAUSE_SCREEN_ENUM, renderer, font, shared_from_this());
		}
	}
	pacman->HandleInput(event);
	return nullptr;
}