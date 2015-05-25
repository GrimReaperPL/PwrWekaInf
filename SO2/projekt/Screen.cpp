#include "Screen.hpp"

Screen::Screen(SDL_Renderer *renderer)
	: m_renderer(renderer)
	, m_square(std::unique_ptr<CarSquare>(new CarSquare()))
	, m_font(nullptr)
{
}

Screen::~Screen()
{
}

void Screen::free()
{
	m_square.get()->endThem();
}

bool Screen::initTextures()
{
	m_font = TTF_OpenFont( "data/pricedown_bl.ttf", 22 );
	if(m_font == NULL)
		return false;
		
	m_text = std::unique_ptr<Texture>(new Texture(m_renderer));
	
	
	for(unsigned int i = 0; i < 10; i++)	// 10 - numer of used textures
		m_textures.push_back(Texture(m_renderer));
		
	if(!m_textures[0].loadFromFile("data/parking.png"))
		return false;
	if(!m_textures[1].loadFromFile("data/mirek.png"))
		return false;
	if(!m_textures[2].loadFromFile("data/brak_hajsu.png"))
		return false;
	if(!m_textures[3].loadFromFile("data/benson.png"))
		return false;
	if(!m_textures[4].loadFromFile("data/Bug2.png"))
		return false;
	if(!m_textures[5].loadFromFile("data/FuroreGT2.png"))
		return false;
	if(!m_textures[6].loadFromFile("data/GT_A12.png"))
		return false;
	if(!m_textures[7].loadFromFile("data/Pickup2.png"))
		return false;
	if(!m_textures[8].loadFromFile("data/Stinger2.png"))
		return false;
	if(!m_textures[9].loadFromFile("data/Z-Type2.png"))
		return false;
	
	return true;
}

void Screen::init(unsigned int width, unsigned int height, unsigned int customers, Mix_Chunk *chunk)
{
	m_width = width;
	m_height = height;
	m_square.get()->init(customers, chunk);
}

void Screen::render()
{
	m_textures[0].render(0,0);	//background texture (number 0)
	//render cars
	std::vector<Car> places = m_square.get()->getPlaces();
	//unsigned int currentX = 0;
	unsigned int currentY = 99;
	const unsigned int step = 86;
	//// left side of the place
	for(unsigned int i = 0; i < 32; i++)
	{
		unsigned int X = step * (i % 4);
		if(i % 4 == 0 && i != 0)
		{
			currentY += 59;
		}
		if(!places[i].m_isFree)
			m_textures[places[i].m_carType].render(X, currentY);
		else if(places[i].m_owner != -1)
		{
			SDL_Color textColor = { 0xFF, 0x00, 0, 0xFF };
			m_text.get()->loadFromRenderedText(std::to_string(places[i].m_owner), textColor, m_font);
			m_text.get()->render(X + 40, currentY + 10);
		}
	}
	//// right side of the place
	currentY = 99;
	for(unsigned int i = 32; i < places.size(); i++)
	{
		unsigned int X = step * (i % 4) + 450;
		if(i % 4 == 0 && i != 32)
		{
			currentY += 59;
		}
		if(!places[i].m_isFree)
			m_textures[places[i].m_carType].render(X, currentY);
		else if(places[i].m_owner != -1)
		{
			SDL_Color textColor = { 0xFF, 0x00, 0, 0xFF };
			m_text.get()->loadFromRenderedText(std::to_string(places[i].m_owner), textColor, m_font);
			m_text.get()->render(X + 50, currentY + 10);
		}
	}
	
	//render customers
	m_textures[1].render(0, m_height - m_textures[1].getHeight());	//mirek's texture (number 1)
	
	//render cash
	SDL_Color textColor = { 0xFF, 0xFF, 0, 0xFF };
	m_text.get()->loadFromRenderedText("$" + std::to_string(m_square.get()->getCash()), textColor, m_font);
	m_text.get()->render(10, 10);
	
	//render customers
	SDL_Color textColor2 = { 0x87, 0xCE, 0xEB, 0xFF };
	m_text.get()->loadFromRenderedText("Number Of Customers: " + std::to_string(m_square.get()->getCustomersWithCash()), textColor2, m_font);
	m_text.get()->render(10, 50);
	
	if(m_square.get()->getCustomersWithCash() == 0)
		m_textures[2].render(116, 175);
	
}
