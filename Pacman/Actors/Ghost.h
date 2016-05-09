#ifndef GHOST_H
#define GHOST_H

#include"../Image/Image.h"
#include"../Map/PacmanMap.h"
#include"../Observer/IObserver.h"
#include"../Actors/Actor.h"
#include"../Graphics/GhostGraphics.h"
#include"../Physics/GhostPhysics.h"
#include"../AI/GhostAI.h"
#include"../Consts/Constants.h"

enum class eGhost {	BLINKY,	PINKY, INKY, CLYDE };

enum class eState {	GHOST_NORMAL, GHOST_DEAD, GHOST_POWERDOWN };

class Ghost : public AIActor, public IObserver, public std::enable_shared_from_this<Ghost>
{
protected:
	int level{ 1 };
	eState ghostState{ eState::GHOST_NORMAL };
	std::shared_ptr<GhostGraphics> gc;
	std::shared_ptr<GhostPhysics> pc;
	std::shared_ptr<GhostAI> ac;

public:
	Ghost() { score = Constants::ghostScore; }
	~Ghost() {}
	void HandleAI(std::shared_ptr<PacmanMap> map) override;
	void HandlePhysics(std::shared_ptr<PacmanMap> map) override;
	void HandleGraphics(std::shared_ptr<SDL_Renderer> renderer) override;
	void setGraphicsComp(std::shared_ptr<GhostGraphics> gComp) { gc = gComp; }
	void setPhysicsComp(std::shared_ptr<GhostPhysics> pComp) { pc = pComp; }
	void setAIComp(std::shared_ptr<GhostAI> aComp) { ac = aComp; }
	void turnNormal();
	void powerdown();
	void die();
	SDL_Point getSpeed() override { return SDL_Point{ 0, 1 }; }
	void setSpeed(SDL_Point speed) override { }
	eState getState() { return ghostState; }
	void setState(eState state) { ghostState = state; }
	int getLevel() { return level; }
	void levelUp() { level++; }
	void update() override;
};


#endif