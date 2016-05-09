#include"DotComponent.h"

void DotComponent::update(std::shared_ptr<Actor> actor)
{
	actor->adjustScore(score);
}