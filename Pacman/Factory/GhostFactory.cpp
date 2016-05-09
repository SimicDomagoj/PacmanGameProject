#include"GhostFactory.h"

std::shared_ptr<Ghost> GhostFactory::getGhost(eGhost type, SDL_Rect initialPosition, std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Actor> actor, std::shared_ptr<Ghost> ghostFollow)
{
	std::shared_ptr<Ghost> ghost = std::make_shared<Ghost>();
	Uint8 blueish[3] = { 0, 255, 255 };
	std::shared_ptr<GhostPhysics> pc = std::make_shared<GhostPhysics>();
	std::shared_ptr<GhostGraphics> gc;
	std::shared_ptr<GhostAI> ac;

	switch (type)
	{
	case eGhost::BLINKY:
		gc = std::make_shared<GhostGraphics>(Constants::blinkyImageLoc, renderer, blueish);
		ac = std::make_shared<BlinkyAI>(actor, SDL_Point{ 15, 0 });
		break;
	case eGhost::PINKY:
		gc = std::make_shared<GhostGraphics>(Constants::pinkyImageLoc, renderer, blueish);
		ac = std::make_shared<PinkyAI>(actor, SDL_Point{ 0, 0 });
		break;
	case eGhost::INKY:
		gc = std::make_shared<GhostGraphics>(Constants::inkyImageLoc, renderer, blueish);
		ac = std::make_shared<InkyAI>(actor, SDL_Point{ 15, 17 }, ghostFollow);
		break;
	case eGhost::CLYDE:
		gc = std::make_shared<GhostGraphics>(Constants::clydeImageLoc, renderer, blueish);
		ac = std::make_shared<ClydeAI>(actor, SDL_Point{ 0, 17 });
		break;
	default:
		break;
	}
	ghost->setPosition(initialPosition);
	ghost->setGraphicsComp(gc);
	ghost->setPhysicsComp(pc);
	ghost->setAIComp(ac);
	return ghost;
}