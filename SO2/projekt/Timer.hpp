#pragma once

#include <SDL2/SDL.h>

class Timer
{
	public:
	Timer();
	~Timer();
	
	void start();
	void stop();
	unsigned int getTicks();
	
	private:
	unsigned int m_startTicks;
	bool m_started;
};
