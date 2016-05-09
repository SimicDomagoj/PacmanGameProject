#ifndef ACTOR_MANIPULATOR_COMPONENT
#define ACTOR_MANIPULATOR_COMPONENT

#include<memory>
#include"../Actors/Actor.h"

class ActorManipulatorComponent
{
public:
	virtual void update(std::shared_ptr<Actor> actor) = 0;
};

#endif