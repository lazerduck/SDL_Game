#pragma once
class Initialisation
{
public:

	Initialisation(void)
	{
	}

	bool start()
	{
		//Initialize SDL
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
			return false;
		}
		else
		{
			//Create window
			window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
			if( window == NULL )
			{
				printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
				return false;
			}
			else
			{
				renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				SDL_RenderSetScale(renderer,scalex,scaley);

				if(renderer == NULL)
				{
					printf("error loading renderer");
					return false;
				}
				SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init(imgFlags)&imgFlags))
				{
					printf("SDL_Image could not start");
					return false;
				}
				//Get window surface
				screenSurface = SDL_GetWindowSurface( window );
			}
		}
		return true;
	}

	~Initialisation(void)
	{

	}

	void Exit(SDL_Window* window, SDL_Surface* screenSurface)
	{
		//Destroy window
		SDL_DestroyWindow( window );
		//Quit SDL subsystems
		SDL_Quit();

	}

	bool DeleteTextures(vector<SDL_Texture*> toCheck)
	{
		int num = 0;
		for(vector<SDL_Texture*>::iterator it = toCheck.begin(); it == toCheck.end();++it)
		{
			SDL_DestroyTexture(*it);
		}
		return true;

	}
};

