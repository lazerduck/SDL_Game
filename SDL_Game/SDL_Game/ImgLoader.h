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
	Map* initMap(Map* map, string path,vector<SDL_Texture*>tiles)
	{
		ifstream ReadFile;
		ReadFile.open(path.c_str());
		int x;
		int y;
		int* data;
		if(ReadFile.is_open())
		{
			ReadFile>>x;
			ReadFile>>y;
			data = new int[x*y];
			int count  = 0;
			while(!ReadFile.eof())
			{
				ReadFile>>*(data+count);
				printf("%d",*(data+count));
				count++;
				if(count%x == 0)
				{
					printf("\n");
				}
			}
		}
		ReadFile.close();
		map = new Map(y,x,data,tiles);
		delete []data;
		return map;
	}
};

