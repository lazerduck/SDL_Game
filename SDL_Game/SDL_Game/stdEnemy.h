#pragma once
class stdEnemy:public Enemy
{
private:
	bool checkedge;
	bool bounce;
	float bouncey;
	SDL_Rect bounceRect;
	gTimer hitTimer;
public:

	stdEnemy(void)
	{
	}
	stdEnemy(SDL_Texture *tex, int X,int Y)
	{
		rot = 0;
		hitcheck = false;
		x = (X*40);
		y = (Y*40)-9;
		dst.x = x;
		dst.y = y;
		health = 10;
		vely = 0;
		velx = 0.1;
		texture = tex;
		SDL_QueryTexture(texture, NULL,NULL,&dst.w,&dst.h);
		dst.h /= 2;
		dst.w /= 2;
		flip = SDL_FLIP_NONE;
		checkedge = true;
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		damage= 10;
		int test = rand()%2;
		if(test == 0)
		{
			bounce = true;
		}
		else
		{
			bounce = false;
		}
		bounceRect = dst;
		bouncey = dst.y;
	}

	void Update(Player* player,Map *map)
	{
		hitTimer.Update(DeltaTime);
		x += velx*DeltaTime;
		y += vely*DeltaTime;
		if(checkedge)
		{
			if(velx>0)
			{
				if(1<<map->GetValue((x+dst.w+1)/40,y/40) & group1 || 1<<map->GetValue((x+dst.w+1)/40,(y+dst.h-1)/40) & group1|| 1<<map->GetValue((x+dst.w+1)/40,(y+dst.h+2)/40) & group2)
				{
					velx = -velx;
				}
			}
			else
			{
				if(1<<map->GetValue((x-1)/40,y/40) & group1 || 1<<map->GetValue((x-1)/40,(y+dst.h-1)/40) & group1||1<<map->GetValue((x-1)/40,(y+dst.h+2)/40) & group2)
				{
					velx = -velx;
				}
			}
		}else
		{
			if(velx>0)
			{
				if(1<<map->GetValue((x+dst.w+1)/40,y/40) & group1 || 1<<map->GetValue((x+dst.w+1)/40,(y+dst.h-1)/40) &group1)
				{
					velx = -velx;
				}
			}
			else
			{
				if(1<<map->GetValue((x-1)/40,y/40) & group1 || 1<<map->GetValue((x-1)/40,(y+dst.h-1)/40) & group1)
				{
					velx = -velx;
				}
			}
		}
		//falling
		if(1<<map->GetValue((x+1)/40,(y+dst.h+1)/40) & group1 || 1<<map->GetValue((x+dst.w-1)/40,(y+dst.h+1)/40) &group1)
		{
			while(1<<map->GetValue((x+1)/40,(y+dst.h)/40) & group1 || 1<<map->GetValue((x+dst.w-1)/40,(y+dst.h)/40) & group1)
			{
				y--;
			}
			vely = 0.0;
			
		}else
		{
			if(vely < 1)
			{
				vely += 0.001*DeltaTime;
			}	

		}
		y+=vely *DeltaTime;
		dst.x =(int) x -camera.x;
		dst.y = (int)y - camera.y;
		bounceRect = dst;

		if(hitcheck&&hitTimer.Time == 0)
		{
			hitTimer.Start();
		}
		if(hitTimer.Time > 100)
		{
			hitcheck = false;
			hitTimer.Stop();
		}
		//bounce
		//bouncey = bounceRect.y;
		if(bounce)
		{
			bouncey += 0.1;
			if(bouncey > dst.y+5)
			{
				bounce = false;
			}
		}
		else
		{
			bouncey -= 0.1;
			if(bouncey < dst.y-5)
			{
				bounce = true;
			}
		}
		if(bouncey > dst.y+5){ bouncey = dst.y+5;}
		if(bouncey < dst.y-5){ bouncey = dst.y-5;}
		bounceRect.y = bouncey;
	}

	void Draw()
	{
		if(hitcheck)
		{
			SDL_SetTextureAlphaMod( texture, 0x40 );
		}
		SDL_RenderCopyEx(renderer, texture,NULL,&bounceRect,rot,NULL,flip);
		if(hitcheck)
		{
			SDL_SetTextureAlphaMod( texture, 0xff );
		}
	}

	~stdEnemy(void)
	{
	}
};

