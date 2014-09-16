#pragma once
class Turret_gun
{
private:
	SDL_Rect dst;
	SDL_Texture* tex;
	float rotation;
	int centx; int centy;
	bool hitcheck;
	SDL_Point cent;
public:
	Turret_gun(void)
	{
	}

	Turret_gun(SDL_Texture* texture, int centX, int centY)
	{
		SDL_QueryTexture(texture,NULL,NULL, &dst.w, &dst.h);
		dst.w /=2; dst.h/= 2;
		dst.x = centX - float(dst.w/2);
		dst.y = (centY - dst.h/float(3/4));
		centx = centX;
		centy = centY;
		tex = texture;
		rotation = 0;
	}
	void update(int centX, int centY, Player* player)
	{
		dst.x = centX +22;
		dst.y = centY - 5;
		centx = centX;
		centy = centY;
		rotation = tan(float(dst.y - player->getY())/float(dst.x - player->getX()))*(180/3.141593);
		rotation += 90;
		cout<<rotation<<endl;
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

