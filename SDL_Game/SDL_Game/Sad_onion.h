#pragma once
class Sad_onion:public Enemy
{
private:
	bool checkedge;
	gTimer hitTimer;
public:

	Sad_onion(void)
	{
	}
	Sad_onion(SDL_Texture *tex, int X,int Y)
	{
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
		flip = SDL_FLIP_NONE;
		checkedge = false;
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		
	}

	void Update(Map *map)
	{
		hitTimer.Update(DeltaTime);
		x += velx*DeltaTime;
		y += vely*DeltaTime;
		if(checkedge)
		{
			if(velx>0)
			{
				if(map->GetValue((x+dst.w+1)/40,y/40) == 1 || map->GetValue((x+dst.w+1)/40,(y+dst.h-1)/40) == 1||map->GetValue((x+dst.w+1)/40,(y+dst.h+2)/40) == 0)
				{
					velx = -velx;
				}
			}
			else
			{
				if(map->GetValue((x-1)/40,y/40) == 1 || map->GetValue((x-1)/40,(y+dst.h-1)/40) == 1||map->GetValue((x-1)/40,(y+dst.h+2)/40) == 0)
				{
					velx = -velx;
				}
			}
		}else
		{
			if(velx>0)
			{
				if(map->GetValue((x+dst.w+1)/40,y/40) == 1 || map->GetValue((x+dst.w+1)/40,(y+dst.h-1)/40) == 1)
				{
					velx = -velx;
				}
			}
			else
			{
				if(map->GetValue((x-1)/40,y/40) == 1 || map->GetValue((x-1)/40,(y+dst.h-1)/40) == 1)
				{
					velx = -velx;
				}
			}
		}
		//falling
		if(map->GetValue((x+1)/40,(y+dst.h+1)/40) == 1 || map->GetValue((x+dst.w-1)/40,(y+dst.h+1)/40) == 1)
		{
			while(map->GetValue((x+1)/40,(y+dst.h)/40) == 1 || map->GetValue((x+dst.w-1)/40,(y+dst.h)/40) == 1)
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

		if(hitcheck&&hitTimer.Time == 0)
		{
			hitTimer.Start();
		}
		if(hitTimer.Time > 100)
		{
			hitcheck = false;
			hitTimer.Stop();
		}
	}


	~Sad_onion(void)
	{
	}
};

