#pragma once
class Enemy
{
protected:
	SDL_Rect dst;
	float x, y, vely, velx;
	int health;
	SDL_Texture *texture;
	SDL_RendererFlip flip;
	bool hitcheck;
	float rot;
public:
	int damage;
	Enemy(void)
	{
	}
	Enemy(SDL_Texture *tex, int X,int Y)
	{
		rot = 0;
		damage= 0;
		x = X*40;
		y = Y*40;
		dst.x = x;
		dst.y = y;
		vely = 0;
		velx = 0;
		SDL_QueryTexture(texture, NULL,NULL,&dst.w,&dst.h);
		flip = SDL_FLIP_NONE;
		hitcheck = false;
	}

	virtual void Update(Player* player,Map *map)
	{
		x += velx*DeltaTime;
		y += vely*DeltaTime;
		dst.x =(int) x -camera.x;
		dst.y = (int)y - camera.y;
	}
	int getHealth()
	{
		return health;
	}
	void Draw()
	{
		if(hitcheck)
		{
			SDL_SetTextureAlphaMod( texture, 0x40 );
		}
		SDL_RenderCopyEx(renderer, texture,NULL,&dst,rot,NULL,flip);
		if(hitcheck)
		{
			SDL_SetTextureAlphaMod( texture, 0xff );
		}
	}
	virtual int hit(int X, int Y,int width,int damage)
	{
		if(X + width > x && X < x + dst.w && Y < y+dst.h && Y+ width > y) 
		{
			
			health -= damage;
			hitcheck = true;
			if(health <=0)
			{
				return 2;
			}
			return 1;
		}
		return 0;
	}
	virtual int hit(SDL_Rect rect,int damage)
	{
		if(rect.x + rect.w > x && rect.x < x + dst.w && rect.y < y+dst.h && rect.y + rect.h > y) 
		{
			health -= damage;
			if(damage >0)
			{
				hitcheck = true;
			}
			if(health <=0)
			{
				return 2;
			}
			return 1;
		}
		return 0;
	}

	virtual ~Enemy(void)
	{
	}
};

