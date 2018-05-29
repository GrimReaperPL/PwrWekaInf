#include "Texture.hpp"

Texture::Texture(SDL_Renderer *renderer)
	: m_texture(nullptr)
	, m_renderer(renderer)
	, m_width(0)
	, m_height(0)
{
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if(loadedSurface == NULL)
	{
		return false;
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if(newTexture == NULL)
		{
			return false;
		}
		else
		{
			//Get image dimensions
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_texture = newTexture;
	return m_texture != nullptr;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font)
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if(textSurface == NULL)
    {
        return false;
    }
    else
    {
        //Create texture from surface pixels
        m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
        if( m_texture == NULL )
        {
            return false;
        }
        else
        {
            //Get image dimensions
            m_width = textSurface->w;
            m_height = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    
    //Return success
    return m_texture != NULL;
}

void Texture::render(int x, int y, SDL_Rect* rect)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, m_width, m_height};

	//Set clip rendering dimensions
	if(rect != nullptr)
	{
		renderQuad.w = rect->w;
		renderQuad.h = rect->h;
	}

	//Render to screen
	SDL_RenderCopy(m_renderer, m_texture, NULL, &renderQuad);
}

int Texture::getWidth() const
{
	return m_width;
}

int Texture::getHeight() const
{
	return m_height;
}

void Texture::free()
{
	//Free texture if it exists
	if(m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}
