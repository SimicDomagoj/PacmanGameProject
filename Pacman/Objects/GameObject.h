#ifndef GAME_OBJECT
#define GAME_OBJECT

#include<SDL.h>
#include<memory>
#include"../Graphics/ObjectGraphicsComponent.h"
#include"../Manipulators/ActorManipulatorComponent.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
protected:
	SDL_Rect position;
	std::shared_ptr<ObjectGraphicsComponent> gc{ nullptr };
	std::shared_ptr<ActorManipulatorComponent> amc{ nullptr };
public:
	SDL_Rect getPosition() { return position; }
	void setPosition(SDL_Rect pos) { position = pos; }
	void setGraphicsComponent(std::shared_ptr<ObjectGraphicsComponent> comp) { gc = comp; }
	void HandleGraphics(std::shared_ptr<SDL_Renderer> renderer)
	{
		if (gc != nullptr)
		{
			gc->Render(shared_from_this(), renderer);
		}
	}
	void setActorManipComponent(std::shared_ptr<ActorManipulatorComponent> comp) { amc = comp; }
	void update(std::shared_ptr<Actor> actor) { if (amc != nullptr) amc->update(actor); }
};

#endif