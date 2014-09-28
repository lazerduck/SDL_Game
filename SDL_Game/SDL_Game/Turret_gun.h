#pragma once
class Turret_gun
{
private:
	SDL_Rect dst;
	SDL_Texture* tex;
	float rotation;
	float rotgoal;
	float rotrad;
	int centx; int centy;
	bool hitcheck;
	SDL_Point cent;
	gTimer shoot_timer;
	bool shoot_check;
	float range;
	float speed;
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
		rotgoal = 0;
		shoot_check = false;
		range = 500;
		speed = 1;
	}
	void update(int centX, int centY, Player* player)
	{
		shoot_timer.Update(DeltaTime);
		dst.x = centX +22;
		dst.y = centY - 5;
		centx = centX;
		centy = centY;
		cent.x = 20;
		cent.y = 18;
		rotrad = 
		rotgoal = std::atan2(float(dst.y - (player->getY()-camera.y)),float(dst.x - (player->getX()-camera.x)))*(180/3.141593);
		float temp = shortest(rotation, rotgoal);
		rotation += temp/30;
		rotrad = (rotation-180) *(3.141593/180);
		if(rotation >= 180)
		{
			rotation -= 360;
		}
		shoot(player);
	}
	void Draw(bool Hit){
		if(Hit)
		{
			SDL_SetTextureAlphaMod( tex, 0x40 );
		}
		SDL_RenderCopyEx(renderer, tex,NULL,&dst,rotation,&cent,SDL_FLIP_NONE);
		if(Hit)
		{
			SDL_SetTextureAlphaMod( tex, 0xff );
		}
	}
	float shortest(float curr, float goal)
	{
		//should be getting between 180 and -180
		curr+=180;
		goal +=180;
		//normalised between 0 and 360
		float short0 = goal - curr;
		float short1 = goal -360 - curr;
		//use abs to get the shortest distance
		if(abs(short0)<abs(short1))
		{
			return short0;
		}
		return short1;
	}
	void shoot(Player *player)
	{
		//range check
		if(pow(float(dst.y-(player->getY()-camera.y)),2) + pow(float(dst.x-(player->getX()-camera.x)),2) < pow(float(range),2)&&shoot_timer.Time == 0)
		{
			shoot_timer.Start();
			for(int i = 0; i<enemybull;i++)
			{
				if(*(posx+i) == -1)
				{
					*(posx+i) = dst.x+(dst.w/2)+camera.x;
					*(posy+i) = dst.y+(dst.h/2)+camera.y;
					
					*(velx+i) = cos(rotrad)*speed;
					*(vely+i) = sin(rotrad) * speed;
					break;
				}
			}
		}
		if(shoot_timer.Time>1000)
		{		
			shoot_timer.Stop();
		}
		
	}
	float lessthan(float val)
	{
		if(val>1)
		{
			val = val - 2*(val-1);
		}
		if(val<-1)
		{
			val = val - 2*(val+1);
		}
		return val;
	}

	~Turret_gun(void)
	{
	}
	float vectormag(float x, float y)
	{
		float tot = x+y;


	}

};

