#ifndef GHOST_AI_H
#define GHOST_AI_H

#include<memory>
#include"../Timer/Timer.h"
#include"../Actors/Actor.h"

class Ghost;

class GhostAI
{
	protected:
		std::shared_ptr<Actor> toFollow;
		SDL_Point homeTile;
		Timer powerdownTime;
		Timer destinationSwitch;
		int timesModeSwitched;
		virtual unsigned int getScatterDuration(int level);
		virtual void deadAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map);
		virtual void normalAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map) = 0;
		virtual void powerdownAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map);
		virtual eDirection findPath(std::shared_ptr<Ghost> ghost, SDL_Point finish, std::shared_ptr<PacmanMap> map);
	public:
		GhostAI(std::shared_ptr<Actor> follow, SDL_Point home) : toFollow{ follow } { homeTile = home; destinationSwitch.start(); }
		void HandleAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map);
		void die(std::shared_ptr<Ghost> ghost);
		void powerdown(std::shared_ptr<Ghost> ghost);
		void turnNormal(std::shared_ptr<Ghost> ghost);
};

class InkyAI : public GhostAI
{
	private:
		std::shared_ptr<Ghost> followGhost;
	protected:
		void normalAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map) override;
	public:
		InkyAI(std::shared_ptr<Actor> follow, SDL_Point home, std::shared_ptr<Ghost> ghost) : followGhost{ ghost }, GhostAI(follow, home) {}
};

class BlinkyAI : public GhostAI
{
protected:
	void normalAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map) override;
public:
	BlinkyAI(std::shared_ptr<Actor> follow, SDL_Point home) : GhostAI(follow, home) {}
};

class PinkyAI : public GhostAI
{
protected:
	void normalAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map) override;
public:
	PinkyAI(std::shared_ptr<Actor> follow, SDL_Point home) : GhostAI(follow, home) {}
};

class ClydeAI : public GhostAI
{
protected:
	void normalAI(std::shared_ptr<Ghost> ghost, std::shared_ptr<PacmanMap> map) override;
public:
	ClydeAI(std::shared_ptr<Actor> follow, SDL_Point home) : GhostAI(follow, home) {}
};

#endif