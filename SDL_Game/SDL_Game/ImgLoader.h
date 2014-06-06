#pragma once
class ImgLoader
{
public:

	ImgLoader(void)
	{
	}

	~ImgLoader(void)
	{
	}

	SDL_Surface* LoadBMP(string path)
	{
		SDL_Surface* optimised = NULL;
		SDL_Surface* loaded = SDL_LoadBMP(path.c_str());
		if(loaded == NULL)
		{
			printf ("Error with %s",path);
		}
		else
		{
			optimised  = SDL_ConvertSurface(loaded,screenSurface->format,NULL);
			if(optimised == NULL)
			{
				printf("unable to optimise %s",path);
			}
			SDL_FreeSurface(loaded);
		}
		return optimised;
	}

	SDL_Surface* LoadPNG(string path)
	{
		SDL_Surface* optimised = NULL;
		SDL_Surface* loaded =  IMG_Load(path.c_str());
		if(loaded == NULL)
		{
			printf("cant load png at %s",path);
		}
		else
		{
			optimised = SDL_ConvertSurface(loaded, screenSurface->format,NULL);
			if( optimised == NULL ) 
			{ 
				printf( "Unable to optimize image %s", path.c_str() );
			}
			SDL_FreeSurface(loaded);
		}
		return optimised;
	}

	SDL_Texture* loadTexturePNG(string path)
	{
		SDL_Texture* tex = NULL;
		SDL_Surface* loaded = IMG_Load(path.c_str());
		if(loaded == NULL)
		{
			printf("error loading png for texture");
		}
		else
		{
			tex = SDL_CreateTextureFromSurface(renderer,loaded);
			if(tex == NULL)
			{
				printf("failed to convert to texture");
			}
			SDL_FreeSurface(loaded);
		}
		return tex;
	}
};
