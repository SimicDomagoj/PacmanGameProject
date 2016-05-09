#include"Font.h"

bool Font::load(std::string fileLocation)
{
	fontLocation = fileLocation;
	if (fileLocation == "")
	{
		return false;
	}
	return true;
}

std::shared_ptr<TTF_Font> Font::getFont(int fontSize)
{
	std::map<int, std::shared_ptr<TTF_Font>>::iterator it;
	it = fontSizes.find(fontSize);

	if (it != fontSizes.end())
	{
		return it->second;
	}
	else
	{
		std::shared_ptr<TTF_Font> mFont = std::shared_ptr<TTF_Font>(TTF_OpenFont(fontLocation.c_str(), fontSize), [](TTF_Font* font) { TTF_CloseFont(font); });
		fontSizes.insert(std::pair<int, std::shared_ptr<TTF_Font>>(fontSize, mFont));
		return mFont;
	}
}