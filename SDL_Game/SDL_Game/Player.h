#pragma once
enum animState {still,run};
class Player
{
	float x;
	float y;
	float speed;
	float fallSpeed;
	bool grounded;
	int health;
	bool jumping;
	float jumpvel;
	int frame;

	animState aState;

	SDL_Rect dst;
	SDL_Rect source;

	SDL_Texture* Sprite;

	SDL_RendererFlip flip;

	gTimer damtimer;
	gTimer jumptimer;
	gTimer animtimer;
public:
	bool hit;
	bool dead;
	Player(void)
	{
	}
	Player(int startX, int startY, SDL_Texture* sprite)
	{
		aState = still;
		dead = false;
		fallSpeed = 0;
		speed = 0.4f;
		x = startX;
		y = startY;
		Sprite = sprite;
		dst.w = 30;
		dst.h = 66;
		dst.x = startX;
		dst.y = startY;
		source.x = 0;
		source.y = 0;
		source.h = 131;
		source.w= 66;
		x = startX;
		y = startY;
		grounded = false;
		flip = SDL_FLIP_NONE;
		health = 100;
		hit = false;
		jumping = false;
		jumpvel = -0.5;
		frame = 1;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	int getHealth(){return health;}
	void Update(Map* map)
	{
		if(damtimer.Time>1000)
		{
			damtimer.Stop();
			SDL_SetTextureAlphaMod( Sprite, 0xff );
			hit = false;
		}
		if(jumptimer.Time<300&&jumping)
		{
			if(!Up)
			{
				jumptimer.Stop();
				jumping = false;
			}
			else
			{
				fallSpeed=jumpvel;
			}
		}
		else
		{
			if(jumptimer.Time!=0)
			{
				jumptimer.Stop();
				jumping = false;
			}
		}
		jumptimer.Update(DeltaTime);
		damtimer.Update(DeltaTime);
		animtimer.Update(DeltaTime);
		y+=fallSpeed *DeltaTime;
		//roof collision
		if(fallSpeed<0)
		{
			if(1<<map->GetValue((x+2)/40,(y-1)/40) & group1 || 1<<map->GetValue((x+dst.w-2)/40,(y-1)/40) & group1)
			{
				int test = (((int)y-1+40)/40)*40;
				test -= y-1;
				y += test;

				fallSpeed = 0.1;

			}
		}
		if(!dead)
		{
			if(Right)
			{
				x += speed*DeltaTime;
				aState = run;
				if(1<<map->GetValue((x+dst.w+1)/40,(y)/40) & group1|| 1<<map->GetValue((x+dst.w+1)/40,(y+dst.h/2)/40) & group1 || 1<<map->GetValue((x+dst.w+1)/40,(y+dst.h)/40) & group1 && 1<<map->GetValue((x-1)/40,(y+dst.h)/40) &group2)
				{
					aState = still;
					int test = (((int)x+dst.w+1)/40)*40;
					test -= x+dst.w+1;
					x += test;
				}
			}

			if(Left)
			{
				x -= speed*DeltaTime;
				aState = run;
				if(1<<map->GetValue((x-1)/40,(y)/40) & group1|| 1<<map->GetValue((x-1)/40,(y+dst.h/2)/40) & group1 || 1<<map->GetValue((x-1)/40,(y+dst.h)/40) & group1 && 1<<map->GetValue((x+dst.w+1)/40,(y+dst.h)/40) & group2)
				{
					aState = still;
					int test = (((int)x-1)/40)*40 + 40;
					test -= x-1;
					x += test;
				}
			}
			if(!Left&&!Right&&!Up)
			{
				aState = still;
			}
		}
		else
		{
			slowTime *=1.01;
		}
		//up and down

		if(1<<map->GetValue((x+2)/40,(y+dst.h+1)/40) & group1 || 1<<map->GetValue((x+dst.w-2)/40,(y+dst.h+1)/40) & group1)
		{
			int test = (((int)y+dst.h+2)/40)*40;
			test -= y+dst.h+1;
			y += test;
			fallSpeed = 0;
			if(Up&&!dead)
			{
				fallSpeed = jumpvel;
				jumping = true;
				jumptimer.Start();
			}
		}
		else
		{
			if(fallSpeed < 1)
			{
				fallSpeed += 0.001*DeltaTime;
			}	
		}
		if(map->GetValue((x+dst.w-2)/40,(y+dst.h+1)/40) == Spike_T||map->GetValue((x+2)/40,(y+dst.h+1)/40) == Spike_T || map->GetValue((x+2)/40,(y-1)/40) == Spike_T||map->GetValue((x+dst.w-2)/40,(y-1)/40) == Spike_T)
		{
			Damage(20);
		}

		camera.Update(x,y,map->getRows(),map->getCols());

		dst.x = x - camera.x;
		dst.y = y - camera.y;
		if(!Space&&!dead)
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
		//update source rectangle

		switch(aState)
		{
		case still:
			source.x = 0;
			source.y = 0;
			animtimer.Stop();
			break;
		case run:
			animtimer.Start();
			if(animtimer.Time>80)
			{
				frame+=1;
				animtimer.Stop();
				if(frame==11) {frame = 1;}
			}
			source.x = source.w + frame*source.w;
			source.y = 0;

			break;
		}
	}
	void Draw()
	{
		SDL_RenderCopyEx(renderer,Sprite,&source,&dst,0.0,NULL,flip);

	}
	bool CirclePoint(int cX, int cY, float rad, int rx, int ry)
	{
		if(std::pow(float(cX-rx),2) + std::pow(float(cY-ry),2) <std::pow(rad,2))
		{
			return true;
		}
		return false;
	}

	bool CircleCollide(int cX, int cY, float rad)
	{
		//is it in range
		if(std::pow(rad+dst.h,2)> std::pow(float(cX-(x-(dst.w/2))),2) + std::pow(float(cY-(y-(dst.h/2))),2))
		{
			//is it between the the x coords
			if(x<cX&&cX<x+dst.w)
			{
				//is it above or below
				if(y-cY<rad&&y-cY>0)
				{
					return true;
				}
				else if(cY-y+dst.h<rad&&cY-y+dst.h>0)
				{
					return true;	
				}

			}
			else if(y<cX&&cY<y+dst.h)
			{
				//is it above or below
				if(x-cX<rad&&x-cX>0)
				{
					return true;
				}
				else if(cX-x+dst.w<rad&&cX-x+dst.w>0)
				{
					return true;	
				}
			}
			else
			{
				if(CirclePoint(cX, cY, rad, x, y))
				{
					return true;
				}
				else if(CirclePoint(cX, cY, rad, x+dst.w, y))
				{
					return true;
				}
				else if(CirclePoint(cX, cY, rad, x, y+dst.h))
				{
					return true;
				}
				else if(CirclePoint(cX, cY, rad, x+dst.w, y+dst.h))
				{
					return true;
				}
			}
		}
		return false;
	}

	void Damage(int dam)
	{
		if(damtimer.Time == 0&&dam!=0&&!hit)
		{
			health -= dam;
			damtimer.Start();
			SDL_SetTextureAlphaMod( Sprite, 0x40 );
			hit = true;
			if(health<=0)
			{
				dead = true;
			}
		}
	}

	SDL_Rect getRect()
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.h = dst.h;
		rect.w = dst.w;
		return rect;
	}

	~Player(void)
	{
		SDL_DestroyTexture(Sprite);
	}
	int hittest(SDL_Rect rect,int damage)
	{
		if(rect.x + rect.w > x && rect.x < x + dst.w && rect.y < y+dst.h && rect.y + rect.h > y) 
		{
			Damage(damage);
			return 1;
		}
		return 0;
	}

	void setpos(int X, int Y)
	{
		x= X;
		y=Y;
		health = 100;
	}
};

