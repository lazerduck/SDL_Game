#pragma once
class Turret_gun
{
private:
	SDL_Rect dst;
	SDL_Texture* tex;
	float rotation;
	int centx; int centy;
	bool hitcheck;

public:
	Turret_gun(void)
	{
	}

	Turret_gun(SDL_Texture* texture, int centX, int centY)
	{
		SDL_QueryTexture(texture,NULL,NULL, &dst.w, &dst.h);
		dst.w /=2; dst.h/= 2;
		dst.x = centX - dst.w/2;
		dst.y = centY - dst.w/float(3/4);
		centx = centX;
		centy = centY;
		tex = texture;
		rotation = 0;
	}
	void update(int centX, int centY)
	{
		dst.x = centX;//- dst.w/2;
		dst.y = centY;
		centx = centX;
		centy = centY;
	}
	void Draw(bool Hit){
		if(Hit)
		{
			SDL_SetTextureAlphaMod( tex, 0x40 );
		}
		SDL_RenderCopyEx(renderer, tex,NULL,&dst,rotation,NULL,SDL_FLIP_NONE);
		if(Hit)
		{
			SDL_SetTextureAlphaMod( tex, 0xff );
		}
	}

	~Turret_gun(void)
	{
	}
};

