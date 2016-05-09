#ifndef FIELD_H
#define FIELD_H

#include<SDL.h>

enum class FieldType { CLEAR_PATH, WALL, CROSSROAD, PACMAN_ONLY_CROSSROAD, CORNER, CAGE, CAGE_ENTRANCE, DOOR };

struct field
{
	FieldType type;
	SDL_Rect area;
	SDL_Color color;
};

#endif