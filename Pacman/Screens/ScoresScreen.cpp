#include"ScoresScreen.h"
#include"../Service/CollisionService.h"
#include"../Service/ScoresHandler.h"

void ScoresScreen::init()
{
	ScoresHandler::get().parseFile(std::ifstream{ Constants::scoresLoc });
	std::vector<std::pair<std::string, int>> s= ScoresHandler::get().getScores();

	background.load_image(Constants::backgroundImageLoc, renderer);
	back.loadFromText("back", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	hallOfFame.loadFromText("hall of fame", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	for (unsigned int i = 0; i < s.size(); ++i)
	{
		scores[i].loadFromText(s[i].first + " " + std::to_string(s[i].second), font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	}
}

void ScoresScreen::render()
{
	background.apply_surface(renderer, 0, 0);
	back.apply_surface(renderer, 100, 50);
	hallOfFame.apply_surface(renderer, (Constants::screenWidth - hallOfFame.getWidth()) / 2, 50);
	for (unsigned int i = 0; i < scores.size(); ++i)
	{
		scores[i].apply_surface(renderer, (Constants::screenWidth - scores[i].getWidth()) / 2, 150 + i * 50);
	}
}

std::shared_ptr<Screen> ScoresScreen::update()
{
	return nullptr;
}

std::shared_ptr<Screen> ScoresScreen::handleEvents(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (CollisionService::checkCollision(back.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				return previousScreen;
			}
		}
	}
	return nullptr;
}