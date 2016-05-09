#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H
#include"../Structures/Field.h"
#include<vector>
#include<memory>

enum class eGhost;

class PacmanMap
{
private:
	std::vector<field> fields;
	std::vector<field> boundaries;
	std::vector<SDL_Rect> dots;
	std::vector<SDL_Rect> pUps;
	std::vector<SDL_Rect> startPositions;
	int width;
	int height;
public:
	PacmanMap(std::string file);
	~PacmanMap();
	FieldType getAtXY(int x, int y);
	void render(std::shared_ptr<SDL_Renderer> renderer);
	std::vector<field> getFields() { return fields; }
	std::vector<field> getBoundaries() { return boundaries; }
	std::vector<SDL_Rect> getDots() { return dots; }
	std::vector<SDL_Rect> getPowerUps() { return pUps; }
	SDL_Rect getPacmanStartPos();
	SDL_Rect getGhostStartPos(eGhost ghost);
};

#endif