#ifndef POWER_UP_COMPONENT
#define POWER_UP_COMPONENT

#include"../Observer/Subject.h"
#include"ActorManipulatorComponent.h"

class PowerUpComponent : public ActorManipulatorComponent, public Subject
{
protected:
	int score;
public:
	PowerUpComponent() = delete;
	PowerUpComponent(int score) { this->score = score; }
	void update(std::shared_ptr<Actor> actor) override;
};

#endif