#pragma once
class Background
{
private:
	SDL_Texture* img;
	SDL_Rect dst;
public:

	Background(void)
	{
	}

	Background(SDL_Texture *Img)
	{
		img = Img;
		dst.x = 0;
		dst.y = 0;
		SDL_QueryTexture(img,NULL,NULL,&dst.w,&dst.h);
		dst.w /= 2;
		dst.h /= 2;
	}
	void Update()
	{

	}
	void Draw()
	{
		SDL_RenderCopy(renderer, img,NULL,&dst);
	}

	~Background(void)
	{
	}
};

