#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"Screens\MainScreen.h"
#include"Timer/Timer.h"
#include<vector>
#include"Service/Options.h"
#include"Service/ScoresHandler.h"
#include"Factory/ScreenFactory.h"
#include"Consts\Constants.h"
int main(int argc, char* argv[])
{
	std::shared_ptr<SDL_Window> window = nullptr;
	std::shared_ptr<SDL_Renderer> renderer = nullptr;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Pac Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::screenWidth, Constants::screenHeight, SDL_WINDOW_SHOWN), [](SDL_Window* wind) { SDL_DestroyWindow(wind); });
		if (window == nullptr)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return 2;
		}
		else
		{
			renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), [](SDL_Renderer* rend) { SDL_DestroyRenderer(rend); });
			if (renderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return 3;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					return 4;
				}
			}
		}
	}
	//initialize ttf
	if (TTF_Init() == -1)
	{
		return 1;
	}
	//set up screen
	SDL_SetWindowIcon(window.get(), SDL_LoadBMP(Constants::iconImageLoc.c_str()));

	//load scores
	ScoresHandler::get().parseFile(std::ifstream{ Constants::scoresLoc });
	//load options
	Options::get().parseFile(std::ifstream{ Constants::optionsLoc });
	//initialize font
	std::shared_ptr<Font> font = std::make_shared<Font>();
	font->load(Constants::fontLoc);
	//initialize screen
	std::shared_ptr<Screen> activeScreen = ScreenFactory::makeScreen(eScreen::MAIN_SCREEN_ENUM, renderer, font);
	font.reset();
	SDL_Event event;
	Timer fps;
	std::shared_ptr<Screen> newScreen;
	// main loop
	bool quit{ false };
	while (!quit)
	{
		fps.start(); 
		while (SDL_PollEvent(&event) != 0)
		{
			newScreen = activeScreen->handleEvents(event);
			if (newScreen != nullptr)
			{
				activeScreen = newScreen;
				newScreen = nullptr;
			}
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		newScreen = activeScreen->update();
		if (newScreen != nullptr)
		{
			activeScreen = newScreen;
			newScreen = nullptr;
			continue;
		}
		
		SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer.get());

		activeScreen->render();

		SDL_RenderPresent(renderer.get());

		if (fps.get_ticks() < 1000 / Constants::fps)
		{
			SDL_Delay((1000 / Constants::fps) - fps.get_ticks());
		}
	}

	ScoresHandler::get().save(std::ofstream{ Constants::scoresLoc });
	Options::get().save(std::ofstream{ Constants::optionsLoc });

	activeScreen = nullptr;
	window = nullptr;
	renderer = nullptr;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}