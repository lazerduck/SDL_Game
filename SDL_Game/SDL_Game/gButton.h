#pragma once
class gButton
{
private:
	SDL_Rect DrawRect;
	SDL_Texture* Up;
	SDL_Texture* Over;
	SDL_Texture* Down;
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
	}

	void Draw()
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

	bool Pressed(int MouseX, int MouseY)
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

