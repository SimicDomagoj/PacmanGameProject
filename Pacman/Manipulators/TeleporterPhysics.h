#ifndef TELEPORTER_PHYSICS
#define TELEPORTER_PHYSICS

#include<memory>
#include"../Actors/Actor.h"
#include"ActorManipulatorComponent.h"

class TeleporterPhysics : public ActorManipulatorComponent
{
	private:
		SDL_Point destination;
	public:
		void setDestination(SDL_Point dest) { destination = dest; }
		void update(std::shared_ptr<Actor> actor) override;
};

#endif