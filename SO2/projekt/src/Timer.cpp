#include "Timer.hpp"

Timer::Timer()
	: m_startTicks(0)
	, m_started(false)
{
}

Timer::~Timer()
{
}

void Timer::start()
{
	m_started = true;
	m_startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	m_started = false;
	m_startTicks = 0;
}

unsigned int Timer::getTicks()
{
	if(m_started)
	{
		return SDL_GetTicks() - m_startTicks;
	}
	else
		return 0;
}
