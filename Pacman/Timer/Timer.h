#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
	unsigned int startTicks;
	unsigned int pausedTicks;

	bool paused;
	bool started;
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	unsigned int get_ticks();

	bool is_started ();
	bool is_paused();
};

#endif