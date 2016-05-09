#ifndef PACMAN_H
#define PACMAN_H

#include"../Image/Image.h"
#include"../Map/PacmanMap.h"
#include"Actor.h"
#include"../Graphics/GraphicsComponent.h"
#include"../Physics/PhysicsComponent.h"
#include"../Input/InputComponent.h"

class Pacman : public UserActor, public std::enable_shared_from_this<Pacman>
{
private:
	SDL_Point speed = SDL_Point{ 0, 0 };
	std::shared_ptr<GraphicsComponent> gc;
	std::shared_ptr<PhysicsComponent> pc;
	std::shared_ptr<InputComponent> ic;
	int lives{ 3 };
public:
	Pacman();
	~Pacman() {}
	void HandleInput(SDL_Event event);
	void HandlePhysics(std::shared_ptr<PacmanMap> map) override;
	void HandleGraphics(std::shared_ptr<SDL_Renderer> renderer) override;
	void setGraphicsComp(std::shared_ptr<GraphicsComponent> gComp) { gc = gComp; }
	void setPhysicsComp(std::shared_ptr<PhysicsComponent> pComp) { pc = pComp; }
	void setInputComp(std::shared_ptr<InputComponent> iComp) { ic = iComp; }
	SDL_Point getSpeed() override;
	void setSpeed(SDL_Point speed) override;
	int getLives();
	void loseLife();
	void setlives(int lives) { this->lives = lives; }
	void lifeUp() { lives++; };
};

#endif