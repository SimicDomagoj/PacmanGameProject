#ifndef FONT_H
#define FONT_H

#include<SDL_ttf.h>
#include<map>
#include<memory>
#include<string>

class Font
{
private:
	std::string fontLocation{ "" };
	std::map<int, std::shared_ptr<TTF_Font>> fontSizes;
public:
	bool load(std::string fileLocation);
	std::shared_ptr<TTF_Font> getFont(int fontSize);
	~Font() {}
};

#endif