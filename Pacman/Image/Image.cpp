#include"Image.h"

void Image::load_image(std::string filename, std::shared_ptr<SDL_Renderer> renderer, Uint8 *colorkey)
{	
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

	SDL_Surface* loadedSurface = nullptr;
	loadedSurface = IMG_Load(filename.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
	}
	else
	{
		if (colorkey != nullptr)
		{
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, *colorkey, *(colorkey + 1), *(colorkey + 2)));
		}
		texture = SDL_CreateTextureFromSurface(renderer.get(), loadedSurface);
		if (texture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
		}
		else
		{
			area.w = loadedSurface->w;
			area.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

void Image::loadFromText(std::string textureText, std::shared_ptr<TTF_Font> font, SDL_Color textColor, std::shared_ptr<SDL_Renderer> renderer)
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(font.get(), textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		texture = SDL_CreateTextureFromSurface(renderer.get(), textSurface);
		if (texture != NULL)
		{
			area.w = textSurface->w;
			area.h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}

void Image::apply_surface(std::shared_ptr<SDL_Renderer> renderer, int x, int y, std::shared_ptr<SDL_Rect> clip)
{
	SDL_Rect renderQuad = { x, y, area.w, area.h };
	area.x = x;
	area.y = y;
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(renderer.get(), texture, clip.get(), &renderQuad);
}

Image::~Image()
{
	SDL_DestroyTexture(texture);
}

int Image::getWidth()
{
	return area.w;
}

int Image::getHeight()
{
	return area.h;
}

void Image::setModulator(SDL_Color color)
{
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

SDL_Color Image::getModulator()
{
	SDL_Color color;
	SDL_GetTextureColorMod(texture, &color.r, &color.g, &color.b);
	return color;
}