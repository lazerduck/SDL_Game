#pragma once
class gButton
{
private:
	SDL_Rect DrawRect;
	SDL_Rect SourceRect;
	SDL_Texture* Up;
	SDL_Texture* Over;
	SDL_Texture* Down;
	bool source;
public:
	int ButtonState;

	gButton(void)
	{
	}

	gButton(int x, int y, int w,int h, SDL_Texture* up)
	{
		DrawRect.x = x;
		DrawRect.y = y;
		DrawRect.w = w;
		DrawRect.h = h;
		Up = up;
		Over = up;
		Down = up;
		ButtonState = 0;
		source = false;
	}
	gButton(int x, int y, int w,int h, SDL_Texture* up,SDL_Texture* over,SDL_Texture* down)
	{
		DrawRect.x = x;
		DrawRect.y = y;
		DrawRect.w = w;
		DrawRect.h = h;
		Up = up;
		Over = over;
		Down = down;
		ButtonState = 0;
		source = false;
	}

	gButton(int x, int y, int w,int h, SDL_Texture* up,bool Source)
	{
		DrawRect.x = x;
		DrawRect.y = y;
		DrawRect.w = w;
		DrawRect.h = h;
		Up = up;
		Over = up;
		Down = up;
		ButtonState = 0;
		source = true;
		SDL_QueryTexture(up,NULL,NULL, &SourceRect.w, &SourceRect.h);
		SourceRect.w = SourceRect.w/3;
		SourceRect.x =0;
		SourceRect.y = 0;
	}

	void Draw()
	{
		if(source)
		{
			if(ButtonState == 0)
			{
				SourceRect.x = 0;
				SDL_RenderCopy(renderer,Up,&SourceRect,&DrawRect);
			}
			if(ButtonState == 1)
			{
				SourceRect.x = SourceRect.w;
				SDL_RenderCopy(renderer,Over,&SourceRect,&DrawRect);
			}
			if(ButtonState == 2)
			{
				SourceRect.x = SourceRect.w*2;
				SDL_RenderCopy(renderer,Down,&SourceRect,&DrawRect);
			}
		}
		else
		{
			if(ButtonState == 0)
			{
				SDL_RenderCopy(renderer,Up,NULL,&DrawRect);
			}
			if(ButtonState == 1)
			{
				SDL_RenderCopy(renderer,Over,NULL,&DrawRect);
			}
			if(ButtonState == 2)
			{
				SDL_RenderCopy(renderer,Down,NULL,&DrawRect);
			}
		}
	}

	bool hit(int x, int y)
	{
		bool hit = true;
		if(x>DrawRect.x*scalex + DrawRect.w*scalex)
		{
			hit = false;
		}
		if(x<DrawRect.x*scalex)
		{
			hit = false;
		}
		if(y>DrawRect.y*scaley + DrawRect.h*scaley)
		{
			hit = false;
		}
		if(y<DrawRect.y*scaley)
		{
			hit = false;
		}
		return hit;
	}

	bool Pressed()
	{
		if(hit(mouseX,mouseY))
		{
			ButtonState = 1;
			if(MouseState == SDL_BUTTON(1))
			{
				ButtonState = 2;
			}
			if(MouseState == 0 && OldMouse == SDL_BUTTON(1))
			{
				return true;
			}
		}
		else
		{
			ButtonState = 0;
		}
		return false;
	}

	~gButton(void)
	{

	}
};

