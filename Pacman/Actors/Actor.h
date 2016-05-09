#ifndef ACTOR_H
#define ACTOR_H

#include"../Map/PacmanMap.h"
#include<SDL.h>

enum class eDirection { DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT };

class Actor
{
	protected:
		eDirection direction{ eDirection::DIRECTION_RIGHT };
		SDL_Rect position;
		int score{ 0 };
	public:
		virtual void HandlePhysics(std::shared_ptr<PacmanMap> map) = 0;
		virtual void HandleGraphics(std::shared_ptr<SDL_Renderer> renderer) = 0;
		void setDirection(eDirection d) { direction = d; }
		eDirection getDirection() { return direction; }
		void setPosition(SDL_Rect pos) { position = pos; }
		SDL_Rect getPosition() { return position; }
		virtual SDL_Point getSpeed() { return SDL_Point{ 0, 0 }; }
		virtual void setSpeed(SDL_Point speed) {}
		void setScore(int newScore) { score = newScore; }
		int getScore() { return score; }
		void adjustScore(int adjustBy) { score += adjustBy; }
};

class AIActor : public Actor
{
	public:
		virtual void HandleAI(std::shared_ptr<PacmanMap> map) = 0;
};

class UserActor : public Actor
{
	public:
		virtual void HandleInput(SDL_Event event) = 0;
};
#endif