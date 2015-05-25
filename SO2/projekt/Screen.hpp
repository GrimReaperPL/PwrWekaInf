#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "CarSquare.hpp"
#include "Texture.hpp"

class Screen
{
	public:
	Screen(SDL_Renderer *renderer);
	~Screen();
	
	bool initTextures();
	void init(unsigned int width, unsigned int height, unsigned int customers, Mix_Chunk *chunk);
	void render();
	
	void free();
	
	private:
	std::vector<Texture> m_textures;
	SDL_Renderer *m_renderer;
	unsigned int m_width;
	unsigned int m_height;
	std::unique_ptr<CarSquare> m_square;
	TTF_Font *m_font;
	std::unique_ptr<Texture> m_text;
};
