#pragma once
class DrawRect
{
private:
	
public:
	SDL_Rect area;
	SDL_Color col;
	DrawRect(void)
	{
	}
	DrawRect(int x, int y, int h, int w)
	{
		area.x = x;
		area.y = y;
		area.h = h;
		area.w = w;
		col.r = 0x00;
		col.g = 0x00;
		col.b = 0x00;
	}
	void setColor(unsigned short r, unsigned short g,unsigned short b)
	{
		col.r = r; col.g = g; col.b = b;
	}

	void Draw()
	{
		SDL_SetRenderDrawColor(renderer, col.r,col.g,col.b,col.a);
		SDL_RenderFillRect(renderer, &area);
	}

	~DrawRect(void)
	{
	}
};

