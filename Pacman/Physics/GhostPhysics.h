#ifndef GHOST_PHYSICS
#define GHOST_PHYSICS

#include<memory>
#include"../Map/PacmanMap.h"
class Ghost;

class GhostPhysics
{
public:
	void update(std::shared_ptr<Ghost> actor, std::shared_ptr<PacmanMap> map);
};

#endif