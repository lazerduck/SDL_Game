#pragma once
class Turret :
	public Enemy
{
private:
	int orientation;
	SDL_Texture* guntex;
	gTimer hitTimer;
	Turret_gun* turr_gun;
public:

	Turret(void)
	{
	}
	Turret(SDL_Texture* tex, SDL_Texture* gun, int X, int Y)
	{
		X*= 40;
		Y*= 40;
		x = X;
		y = Y;
		texture = tex;
		guntex = gun;
		dst.x = x;
		dst.y = y;
		SDL_QueryTexture(texture,NULL,NULL,&dst.w,&dst.h);
		dst.h /= 2;
		dst.w /=2;
		vely = 0;
		velx = 0;
		health = 10;
		texture = tex;
		damage = 0;
		hitcheck = false;
		flip = SDL_FLIP_NONE;
		turr_gun = new Turret_gun(gun,X-5,Y - dst.h/2);
	}

	void Update(Player* player,Map *map)
	{
		hitTimer.Update(DeltaTime);
		dst.x = x - camera.x;
		dst.y = y - camera.y;
		turr_gun->update(dst.x,dst.y);
		if(1<<map->GetValue(x/40,(y/40) -1) & group1)
		{
			rot = 180;
			dst.y --;
		}
		else if(1<<map->GetValue(x/40,(y/40)+1) & group1)
		{
			rot = 0;
		}
		else if(1<<map->GetValue((x/40)+1,y/40) & group1)
		{
			rot = 270;
		}
		else if(1<<map->GetValue((x/40)-1,y/40) & group1)
		{
			dst.x --;
			rot = 90;
		}
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

	void Draw() override
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
		turr_gun->Draw(hitcheck);
	}

	~Turret(void)
	{
		delete turr_gun;
	}
};

