#include"GameObjectFactory.h"
#include"../Graphics/SimpleGraphicsComponent.h"
#include"../Manipulators/TeleporterPhysics.h"
#include"../Manipulators/PowerUpComponent.h"
#include"../Manipulators/DotComponent.h"
#include"../Consts/Constants.h"

std::vector<std::shared_ptr<GameObject>> GameObjectFactory::getDots(std::vector<SDL_Rect> positions, std::shared_ptr<SDL_Renderer> renderer)
{
	std::vector<std::shared_ptr<GameObject>> objs;
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	for (unsigned int i = 0; i < positions.size(); ++i)
	{
		obj->setPosition(positions[i]);
		obj->setGraphicsComponent(std::make_shared<SimpleGraphicsComponent>(Constants::dotImageLoc, renderer));
		obj->setActorManipComponent(std::make_shared<DotComponent>(Constants::dotScore));
		objs.push_back(obj);
		obj = std::make_shared<GameObject>();
	}
	return objs;
}
std::vector<std::shared_ptr<GameObject>> GameObjectFactory::getPowerUps(std::vector<SDL_Rect> positions, std::shared_ptr<SDL_Renderer> renderer, std::vector<std::shared_ptr<IObserver>> observers)
{
	std::vector<std::shared_ptr<GameObject>> objs;
	
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	for (unsigned int i = 0; i < positions.size(); ++i)
	{
		std::shared_ptr<PowerUpComponent> amc = std::make_shared<PowerUpComponent>(Constants::powerupScore);
		for (unsigned int j = 0; j < observers.size(); ++j)
		{
			amc->attach(observers[j]);
		}
		obj->setActorManipComponent(amc);
		obj->setPosition(positions[i]);
		obj->setGraphicsComponent(std::make_shared<SimpleGraphicsComponent>(Constants::pUpImageLoc, renderer));
		objs.push_back(obj);
		obj = std::make_shared<GameObject>();
	}
	return objs;
}
std::vector<std::shared_ptr<GameObject>> GameObjectFactory::getTeleporter(std::vector<SDL_Rect> positions, std::vector<SDL_Point> destinations, std::shared_ptr<SDL_Renderer> renderer)
{
	std::vector<std::shared_ptr<GameObject>> objs;
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	for (unsigned int i = 0; i < positions.size(); ++i)
	{
		std::shared_ptr<TeleporterPhysics> amc = std::make_shared<TeleporterPhysics>();
		amc->setDestination(destinations[i]);
		obj->setPosition(positions[i]);
		obj->setActorManipComponent(amc);
		objs.push_back(obj);
		obj = std::make_shared<GameObject>();
	}
	return objs;
}