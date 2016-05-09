#ifndef PHYSICS_COMPONENT
#define PHYSICS_COMPONENT

#include<memory>
#include"../Map/PacmanMap.h"
#include"../Actors/Actor.h"

class PhysicsComponent
{
	public:
		virtual void Update(std::shared_ptr<Actor> actor, std::shared_ptr<PacmanMap> map) = 0;
};

#endif