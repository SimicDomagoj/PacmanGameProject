#ifndef PACMAN_PHYSICS
#define PACMAN_PHYSICS

#include"PhysicsComponent.h"

class PacmanPhysics : public PhysicsComponent
{
	void Update(std::shared_ptr<Actor> actor, std::shared_ptr<PacmanMap> map) override;
};

#endif