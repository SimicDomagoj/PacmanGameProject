#ifndef DOT_COMPONENT
#define DOT_COMPONENT

#include"ActorManipulatorComponent.h"

class DotComponent : public ActorManipulatorComponent
{
protected:
	int score;
public:
	DotComponent() = delete;
	DotComponent(int score) { this->score = score; }
	void update(std::shared_ptr<Actor> actor) override;
};

#endif