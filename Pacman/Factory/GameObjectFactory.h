#ifndef GAEM_OBJECT_FACTORY
#define GAEM_OBJECT_FACTORY

#include"../Objects/GameObject.h"
#include<memory>
#include"../Observer/IObserver.h"
#include<vector>

class GameObjectFactory
{
public:
	static std::vector<std::shared_ptr<GameObject>> getDots(std::vector<SDL_Rect> positions, std::shared_ptr<SDL_Renderer> renderer);
	static std::vector<std::shared_ptr<GameObject>> getPowerUps(std::vector<SDL_Rect> positions, std::shared_ptr<SDL_Renderer> renderer, std::vector<std::shared_ptr<IObserver>> observers);
	static std::vector<std::shared_ptr<GameObject>> getTeleporter(std::vector<SDL_Rect> positions, std::vector<SDL_Point> destinations, std::shared_ptr<SDL_Renderer> renderer);
};

#endif