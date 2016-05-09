#include"PowerUpComponent.h"

void PowerUpComponent::update(std::shared_ptr<Actor> actor)
{
	actor->adjustScore(score);
	notify();
}