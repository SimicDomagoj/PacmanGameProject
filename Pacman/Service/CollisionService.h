#ifndef COLLISION_SERVICE
#define COLLISION_SERVICE

#include<memory>
#include"../Actors/Ghost.h"

class CollisionService
{
public:
	static bool checkCollision(SDL_Rect A, SDL_Rect B);
	static bool checkCollision(SDL_Rect r, SDL_Point p);
	static bool checkCollision(std::shared_ptr<Actor> ghost, std::shared_ptr<PacmanMap> map);
	static bool checkCollision(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map);
	static bool checkCollision(std::shared_ptr<Actor> actor, std::shared_ptr<Ghost> ghost);
};

#endif