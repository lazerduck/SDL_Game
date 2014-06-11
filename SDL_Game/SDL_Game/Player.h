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
		dst.x = playerX+x;
		dst.y = playerY+y;
		dst.h = 53;
		dst.w = 19;
		grounded = false;

	}
	void Update(Map* map)
	{
		float ypos = y+52;
		float xpos = 0;
		int val = 0;
		if(Left)
		{
			 
			xpos = x-speed*DeltaTime;
			val = map->GetValue(xpos/40,ypos/40);
			if(val != 1)
			{
				ypos = y;
				val = map->GetValue(xpos/40,ypos/40);
				if(val != 1)
				{
					ypos = y+27;
					val = map->GetValue(xpos/40,ypos/40);
					if(val != 1)
					{
						x = xpos;
					}
				}
			}
		}

		if(Right)
		{
			xpos = x+speed*DeltaTime;
			val = map->GetValue((xpos+19)/40,ypos/40);
			if(val != 1)
			{
				ypos = y;
				val = map->GetValue((xpos+19)/40,ypos/40);
				if(val != 1)
				{
					ypos = y+27;
					val = map->GetValue((xpos+19)/40,ypos/40);
					if(val != 1)
					{
						x = xpos;
					}
				}
			}
		}
		if(Up)
		{
			if(grounded)
			{
				fallSpeed = -0.5;
				grounded = false;
				y-=0.01;
			}
		}
		playerX = MIDX-(int)x;
		
		ypos = y+53;
		xpos = x;
		val = map->GetValue(xpos/40,ypos/40);
		if(val!=1)
		{
			xpos = x+19;
			val = map->GetValue(xpos/40,ypos/40);
		}
		if(val== 1)
		{
			grounded = true;
		}
		else
		{
			grounded = false;
		}

		if(!grounded)
		{
			ypos = y-1;
			xpos = x;
			val = map->GetValue(xpos/40,ypos/40);
			if(fallSpeed<0)
			{
				if(val == 1)
				{
					fallSpeed = 0;
				}
				else
				{
					xpos = x+19;
					val = map->GetValue(xpos/40,ypos/40);
					if(val == 1)
					{
						fallSpeed = 0;
					}
				}
			}
			if(fallSpeed<0.5)
			{
				fallSpeed+= 0.001*DeltaTime;
			}
			y+= fallSpeed*DeltaTime;
		}
		else
		{
			fallSpeed = 0;
		}
		playerY = MIDY-(int)y;
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

