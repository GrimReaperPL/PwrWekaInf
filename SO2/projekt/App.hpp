#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <memory>

#include "Timer.hpp"
#include "Screen.hpp"

class App
{
	public:
	App(unsigned int width, unsigned int height, unsigned int customers);
	~App();
	int run();
	
	private:
	bool init();
	void cleanUp();
	void render();
	
	unsigned int m_width;
	unsigned int m_height;
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	bool m_shutdown;
	std::unique_ptr<Screen> m_screen;
	Mix_Music *m_music;
	unsigned int m_customers;
	Mix_Chunk *m_ching;
};

