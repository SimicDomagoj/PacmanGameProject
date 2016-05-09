#ifndef INPUT_COMPONENT
#define INPUT_COMPONENT

#include<memory>
#include"../Actors/Actor.h"

class InputComponent
{
public:
	virtual void handleInput(std::shared_ptr<Actor> actor, SDL_Event event) = 0;
};

#endif