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
		flip = SDL_FLIP_NONE;
		checkedge = true;
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		damage= 10;
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

