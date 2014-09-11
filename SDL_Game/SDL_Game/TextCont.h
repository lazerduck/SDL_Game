#pragma once
class TextCont
{
private:
	TTF_Font *Font;
	SDL_Texture *texture;
public:

	TextCont(void)
	{
		TTF_Init();
		Font = TTF_OpenFont( "fonts/SourceSansPro-Bold.otf", 38 );
		if(Font == NULL)
		{
			printf("error making font");
		}
	}

	~TextCont(void)
	{
		TTF_CloseFont(Font);
	}

	SDL_Texture* CreateText(std::string inputText, SDL_Color textColor)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(Font,inputText.c_str(), textColor);
		if( textSurface == NULL ) { 
			printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); 
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		}
		SDL_FreeSurface(textSurface);
		return texture;
	}
};

