#include<SDL_ttf.h>
#include<memory>
#include<string>
#include<SDL.h>
#include<SDL_image.h>

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
protected: 
	SDL_Rect area;
	SDL_Texture* texture{ nullptr };
	void* pixels{ nullptr };
	int pitch{ 0 };

public:
	Image() {
		texture = nullptr;
	};
	~Image();
	void load_image(std::string filename, std::shared_ptr<SDL_Renderer> renderer, Uint8 *colorkey = NULL);
	void apply_surface(std::shared_ptr<SDL_Renderer> renderer, int x, int y, std::shared_ptr<SDL_Rect> clip = NULL);
	void loadFromText(std::string textureText, std::shared_ptr<TTF_Font> font, SDL_Color textColor, std::shared_ptr<SDL_Renderer> renderer);
	int getWidth();
	int getHeight();
	SDL_Rect getArea() { return area; }
	void setModulator(SDL_Color color);
	SDL_Color getModulator();
};

#endif