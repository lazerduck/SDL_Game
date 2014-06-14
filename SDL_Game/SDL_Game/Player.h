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
public:

	Player(void)
	{
	}
	Player(int startX, int startY, SDL_Texture* sprite)
	{
		fallSpeed = 0;
		speed = 0.2f;
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
	}
	void Update(Map* map)
	{
		//left and right
		if(Right)
		{
			if(map->GetValue((dst.x+dst.w)/40,dst.y/40) ==0)
			{
				if(map->GetValue((dst.x+dst.w)/40,(dst.y+dst.h/2)/40) ==0)
				{
					if(map->GetValue((dst.x+dst.w)/40,(dst.y+dst.h)/40) ==0)
					{
						x += speed*DeltaTime;
					}
				}
			}

		}

		if(Left)
		{
			if(map->GetValue(dst.x/40,dst.y/40) ==0)
			{
				if(map->GetValue(dst.x/40,(dst.y+dst.h/2)/40) ==0)
				{
					if(map->GetValue(dst.x/40,(dst.y+dst.h)/40) ==0)
					{
						x -= speed*DeltaTime;
					}
				}
			}

		}
		//up and down
		if(map->GetValue((dst.x+1)/40,(dst.y+dst.h+1)/40) == 1 || map->GetValue((dst.x+dst.w-1)/40,(dst.y+dst.h+1)/40) == 1)
		{
			fallSpeed = 0;
			if(Up)
			{
				fallSpeed = -0.2;
			}
		}
		else
		{
			if(fallSpeed < 0.2)
			{
				fallSpeed += 0.001*DeltaTime;
			}	
		}
		y+=fallSpeed;
		dst.x = x - camera.x;
		dst.y = y - camera.y;
	}
	void Draw()
	{
		SDL_RenderCopy(renderer,Sprite,NULL,&dst);
	}

	~Player(void)
	{
		SDL_DestroyTexture(Sprite);
	}
};

