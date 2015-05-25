#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Texture
{
	public:
	Texture();
	Texture(SDL_Renderer *renderer);
	~Texture();
	
	bool loadFromFile(std::string path);
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font);
	void render(int x, int y, SDL_Rect *rect = nullptr);
	int getWidth() const;
	int getHeight() const;
	void free();
	
	private:
	SDL_Texture *m_texture;
	SDL_Renderer *m_renderer;
	int m_width;
	int m_height;
};
