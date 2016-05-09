#include"OptionsScreen.h"
#include"../Service/CollisionService.h"
#include"../Service/Options.h"

void OptionsScreen::init()
{
	background.load_image(Constants::backgroundImageLoc, renderer);
	back.loadFromText("back", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	on.loadFromText("on", font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	off.loadFromText("off", font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	keys.loadFromText("wasd", font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	arrows.loadFromText("arrows", font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	windowed.loadFromText("windowed", font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	fullScreen.loadFromText("full screen", font->getFont(40), SDL_Color{ 255, 255, 255 }, renderer);
	slash.loadFromText("/", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	sound.loadFromText("sound", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	keybindings.loadFromText("key bindings", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);
	windowSize.loadFromText("window size", font->getFont(40), SDL_Color{ 0, 0, 0 }, renderer);

	if (Options::get().getValue("keybindings") == "keys")
	{
		keys.setModulator(SDL_Color{ 0, 0, 0 });
		arrows.setModulator(SDL_Color{ 128, 128, 128 });
	}
	else
	{
		arrows.setModulator(SDL_Color{ 0, 0, 0 });
		keys.setModulator(SDL_Color{ 128, 128, 128 });
	}
	if (Options::get().getValue("sound") == "on")
	{
		on.setModulator(SDL_Color{ 0, 0, 0 });
		off.setModulator(SDL_Color{ 128, 128, 128 });
	}
	else
	{
		off.setModulator(SDL_Color{ 0, 0, 0 });
		on.setModulator(SDL_Color{ 128, 128, 128 });
	}
	if (Options::get().getValue("windowsize") == "windowed")
	{
		windowed.setModulator(SDL_Color{ 0, 0, 0 });
		fullScreen.setModulator(SDL_Color{ 128, 128, 128 });
	}
	else
	{
		fullScreen.setModulator(SDL_Color{ 0, 0, 0 });
		windowed.setModulator(SDL_Color{ 128, 128, 128 });
	}
}

void OptionsScreen::render()
{
	background.apply_surface(renderer, 0, 0);
	back.apply_surface(renderer, 100, 50);	
	sound.apply_surface(renderer, 200, 200);
	slash.apply_surface(renderer, 480, 200);
	on.apply_surface(renderer, 400, 200);
	off.apply_surface(renderer, 520, 200);
	keybindings.apply_surface(renderer, 250, 300);
	keys.apply_surface(renderer, 450, 400);
	arrows.apply_surface(renderer, 150, 400);
	windowSize.apply_surface(renderer, 250, 500);
	windowed.apply_surface(renderer, 150, 600);
	fullScreen.apply_surface(renderer, 450, 600);
}

std::shared_ptr<Screen> OptionsScreen::update()
{
	return nullptr;
}

std::shared_ptr<Screen> OptionsScreen::handleEvents(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (CollisionService::checkCollision(back.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				return previousScreen;
			}
			else if (Options::get().getValue("sound") == "off" && CollisionService::checkCollision(on.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				Options::get().setValue("sound", "on");
				on.setModulator(SDL_Color{ 0, 0, 0 });
				off.setModulator(SDL_Color{ 128, 128, 128 });
			}
			else if (CollisionService::checkCollision(off.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				Options::get().setValue("sound", "off");
				off.setModulator(SDL_Color{ 0, 0, 0 });
				on.setModulator(SDL_Color{ 128, 128, 128 });
			}
			else if (Options::get().getValue("keybindings") == "arrows" && CollisionService::checkCollision(keys.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				Options::get().setValue("keybindings", "keys");
				keys.setModulator(SDL_Color{ 0, 0, 0 });
				arrows.setModulator(SDL_Color{ 128, 128, 128 });
			}
			else if (CollisionService::checkCollision(arrows.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				Options::get().setValue("keybindings", "arrows");
				keys.setModulator(SDL_Color{ 128, 128, 128 });
				arrows.setModulator(SDL_Color{ 0, 0, 0 });
			}
			else if (Options::get().getValue("windowsize") == "fullscreen" && CollisionService::checkCollision(windowed.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				Options::get().setValue("windowsize", "windowed");
				windowed.setModulator(SDL_Color{ 0, 0, 0 });
				fullScreen.setModulator(SDL_Color{ 128, 128, 128 });
			}
			else if (CollisionService::checkCollision(fullScreen.getArea(), SDL_Point{ event.button.x, event.button.y }))
			{
				Options::get().setValue("windowsize", "fullscreen");
				fullScreen.setModulator(SDL_Color{ 0, 0, 0 });
				windowed.setModulator(SDL_Color{ 128, 128, 128 });
			}
		}
	}
	return nullptr;
}