#ifndef CONSTANTS_H
#define CONSTANTS_H

#include<string>

namespace Constants
{
	const int speed = 1;
	const int screenWidth = 960;
	const int screenHeight = 720;
	const int fps = 60;
	const int mapStartXPos = 180;
	const int mapStartYPos = 20;
	const int tileWidth = 40;
	const int tileHeight = 40;
	const int minScatterTime = 20;
	const int breakPointLevel = 10;
	const int clydeTileProximity = 8;
	const int powerdownDuration = 8000;
	const int dotScore = 10;
	const int powerupScore = 50;
	const int ghostScore = 150;
	const int maxNameLenght = 10;
	const int maxLives = 10;
	const int lifeUpScore = 10000;
	const std::string dotImageLoc = "Resources/dot.png";
	const std::string pUpImageLoc = "Resources/powerup.png";
	const std::string backgroundImageLoc = "Resources/bg1.png";
	const std::string blinkyImageLoc = "Resources/blinkyBitmap.png";
	const std::string pinkyImageLoc = "Resources/pinkyBitmap.png";
	const std::string inkyImageLoc = "Resources/inkyBitmap.png";
	const std::string clydeImageLoc = "Resources/clydeBitmap.png";
	const std::string transitionImageLoc = "Resources/lvltrns.png";
	const std::string pacmanImageLoc = "Resources/pacmanBitmap.png";
	const std::string cuteGhostsImageLoc = "Resources/pghosts.png";
	const std::string mapLoc = "Resources/map.txt";
	const std::string optionsLoc = "Resources/options";
	const std::string scoresLoc = "Resources/score";
	const std::string fontLoc = "Resources/oneway.ttf";
	const std::string lifeImageLoc = "Resources/life.png";
	const std::string iconImageLoc = "Resources/icon.bmp";
}

#endif