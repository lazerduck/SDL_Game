#pragma once
class Enemy
{
protected:
	SDL_Rect dst;
	float x, y, vely, velx;
	int health;
	SDL_Texture *texture;
	SDL_RendererFlip flip;
public:

	Enemy(void)
	{
	}
	Enemy(SDL_Texture *tex, int X,int Y)
	{
		x = X*40;
		y = Y*40;
		dst.x = x;
		dst.y = y;
		vely = 0;
		velx = 0;
		SDL_QueryTexture(texture, NULL,NULL,&dst.w,&dst.h);
		flip = SDL_FLIP_NONE;
	}

	virtual void Update(Map *map)
	{
		x += velx*DeltaTime;
		y += vely*DeltaTime;
		dst.x =(int) x -camera.x;
		dst.y = (int)y - camera.y;
	}

	void Draw()
	{
		SDL_RenderCopyEx(renderer, texture,NULL,&dst,0.0,NULL,flip);
	}
	int hit(int X, int Y,int width,int damage)
	{
		if(collision(X,Y) || collision(X+width,Y)||collision(X,Y) || collision(X+width,Y+width))
		{
			health -= damage;
			printf("hit\n");
			if(health <=0)
			{
				return 2;
			}
			return 1;
		}
		return 0;
	}
	bool collision(int X, int Y)
	{
		if(X>x && X<x+dst.w && Y>y&&Y<y+dst.h)
		{
			return true;
		}
		return false;
	}

	~Enemy(void)
	{
	}
};

