#pragma once
class gButton
{
private:
	SDL_Rect DrawRect;
	SDL_Texture* Up;
public:

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
	}

	void Draw()
	{
		SDL_RenderCopy(renderer,Up,NULL,&DrawRect);
	}

	bool hit(int x, int y)
	{
		bool hit = true;
		if(x>DrawRect.x + DrawRect.w)
		{
			hit = false;
		}
		if(x<DrawRect.x)
		{
			hit = false;
		}
		if(y>DrawRect.y + DrawRect.h)
		{
			hit = false;
		}
		if(y<DrawRect.y)
		{
			hit = false;
		}
		return hit;
	}

	~gButton(void)
	{
	}
};

