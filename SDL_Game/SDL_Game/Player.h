#pragma once
class Player
{
	float x;
	float y;
	float speed;
	float fallSpeed;
	bool grounded;
	
	SDL_Rect dst;

	SDL_Texture* Sprite;

	SDL_RendererFlip flip;
public:

	Player(void)
	{
	}
	Player(int startX, int startY, SDL_Texture* sprite)
	{
		fallSpeed = 0;
		speed = 0.4f;
		x = startX;
		y = startY;
		Sprite = sprite;
		playerX = MIDX-(int)x;
		playerY = MIDY-(int)y;
		SDL_QueryTexture(sprite,NULL,NULL,&dst.w,&dst.h);
		dst.x = startX;
		dst.y = startY;
		x = startX;
		y = startY;
		grounded = false;
		flip = SDL_FLIP_NONE;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	void Update(Map* map)
	{
		y+=fallSpeed *DeltaTime;
		if(Right)
		{
			x += speed*DeltaTime;
			if(map->GetValue((x+dst.w+1)/40,(y)/40) ==1|| map->GetValue((x+dst.w+1)/40,(y+dst.h/2)/40) ==1 || map->GetValue((x+dst.w+1)/40,(y+dst.h)/40) ==1&&map->GetValue((x-1)/40,(y+dst.h)/40) !=1)
			{
				int test = (((int)x+dst.w+1)/40)*40;
				test -= x+dst.w+1;
				x += test;
			}
		}

		if(Left)
		{
			x -= speed*DeltaTime;
			if(map->GetValue((x-1)/40,(y)/40) ==1|| map->GetValue((x-1)/40,(y+dst.h/2)/40) ==1 || map->GetValue((x-1)/40,(y+dst.h)/40) ==1 && map->GetValue((x+dst.w+1)/40,(y+dst.h)/40) !=1)
			{
				int test = (((int)x-1)/40)*40 + 40;
				test -= x-1;
				x += test;
			}
		}
		//up and down

		if(map->GetValue((x+2)/40,(y+dst.h+2)/40) == 1 || map->GetValue((x+dst.w-2)/40,(y+dst.h+2)/40) == 1)
		{
			int test = (((int)y+dst.h+2)/40)*40;
			test -= y+dst.h+2;
			y += test;
			fallSpeed = 0;
			if(Up)
			{
				fallSpeed = -0.7;
			}
			dst.y = (dst.y/40)*40 + 1;
		}
		else 
		{
			if(map->GetValue((x+2)/40,(y-1)/40) == 1 || map->GetValue((x+dst.w-2)/40,(y-1)/40) == 1)
			{
				if(fallSpeed <0)
				{
				fallSpeed = 0.1;
				}
			}else
			{
				if(fallSpeed < 1)
				{
					fallSpeed += 0.001*DeltaTime;
				}	
			}
		}
		

		camera.Update(x,y,map->getRows(),map->getCols());

		dst.x = x - camera.x;
		dst.y = y - camera.y;
		if(!Space)
		{
			if(Right)
			{
				flip = SDL_FLIP_NONE;
			}
			if(Left)
			{
				flip = SDL_FLIP_HORIZONTAL;
			}
		}
	}
	void Draw()
	{
		SDL_RenderCopyEx(renderer,Sprite,NULL,&dst,0.0,NULL,flip);
	}

	~Player(void)
	{
		SDL_DestroyTexture(Sprite);
	}
};

