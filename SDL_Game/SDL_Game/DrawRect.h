#pragma once
class DrawRect
{
private:
	
public:
	SDL_Rect area;
	DrawRect(void)
	{
	}
	DrawRect(int x, int y, int h, int w)
	{
		area.x = x;
		area.y = y;
		area.h = h;
		area.w = w;
	}

	void Draw()
	{
		SDL_RenderFillRect(renderer, &area);
	}

	~DrawRect(void)
	{
	}
};

