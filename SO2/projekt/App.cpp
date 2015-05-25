#include "App.hpp"

App::App(unsigned int width, unsigned int height, unsigned int customers)
	: m_width(width)
	, m_height(height)
	, m_window(nullptr)
	, m_renderer(nullptr)
	, m_shutdown(false)
	, m_screen(std::unique_ptr<Screen>(nullptr))
	, m_music(nullptr)
	, m_customers(customers)
{
	
}

App::~App()
{
}

int App::run()
{
	if(!init())
		return -1;
		
	SDL_Event event;
	Timer capTimer;
	
	Mix_PlayMusic(m_music, -1);
	
	while(!m_shutdown)
	{
		capTimer.start();
		
		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_QUIT)
			{
				m_shutdown = true;
			}
		}
		
		render();
		
		unsigned int frameTicks = capTimer.getTicks();
		if(frameTicks < (1000 / 60))	//60FPS
		{
			SDL_Delay((1000 / 60) - frameTicks);
		}
	}
	
	Mix_FreeMusic(m_music);
	
	cleanUp();
		
	return 0;
}

void App::render()
{
	//SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	
	SDL_RenderClear(m_renderer);
	//
	// render here
	m_screen.get()->render();
	//
	SDL_RenderPresent(m_renderer);
}

bool App::init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}
	
	m_window = SDL_CreateWindow("SO2 - Projekt",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          m_width, m_height,
                          SDL_WINDOW_SHOWN);
    if(m_window == NULL)
		return false;
		
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if(m_renderer == NULL)
		return false;
		
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}
	
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	
	int imgFlags = IMG_INIT_PNG;
	if( !(IMG_Init(imgFlags) & imgFlags))
		return false;
		
	if( TTF_Init() == -1 )
		return false;
		
	m_screen = std::unique_ptr<Screen>(new Screen(m_renderer));
	
	if(!m_screen.get()->initTextures())
	{
		std::cout << "Error loading images\n";
		return false;
	}
	
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Error loading mixer\n";
		return false;
	}
	
	m_music = Mix_LoadMUS("data/Young Daddy.ogg");
	if(m_music == NULL)
	{
		std::cout << "Error loading music\n";
		return false;
	}
	
	m_ching = Mix_LoadWAV("data/cash_register.wav");
	if(m_ching == NULL)
        std::cout << "Can't load ka-ching\n";
        
	m_screen.get()->init(m_width, m_height, m_customers, m_ching);
		
	return true;
}

void App::cleanUp()
{
	m_screen.get()->free();
	Mix_FreeChunk(m_ching);
	Mix_CloseAudio();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
