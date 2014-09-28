
class Weapon
{
private:
	SDL_Texture* gunSprite;
	SDL_Texture* bullet;
	float* bulletX;
	float* bulletY;
	float* velX;
	float* velY;
	int bullets;
	SDL_Rect dst;
	float x;
	float y;
	gTimer timer1;
	bool dir; // true = right
	SDL_RendererFlip flip;
public:

	Weapon(void)
	{
	}
	Weapon(SDL_Texture* texture,SDL_Texture* bullet_tex, Player &player)
	{
		bullets = 100;
		gunSprite = texture;
		bullet = bullet_tex;
		dst.x = player.getX()+3- camera.x;
		dst.y = player.getY();
		SDL_QueryTexture(gunSprite, NULL,NULL,&dst.w,&dst.h);
		//14 20
		dst.w = 25;
		dst.h = 11;
		bulletX = new float[bullets];
		bulletY = new float[bullets];
		velX = new float[bullets];
		velY = new float[bullets];
		for(int i = 0;i<bullets;i++)
		{
			*(bulletX+i) = -1;
			*(bulletY+i) = -1;
			*(velX+i) = 0;
			*(velY+i) = 0;
		}
		dir = true;
		flip = SDL_FLIP_NONE;
	}
	void Update(Player &player, Map *map)
	{
		if(player.hit)
		{
			SDL_SetTextureAlphaMod( gunSprite, 0x40 );
		}
		else
		{
			SDL_SetTextureAlphaMod( gunSprite, 0xff );
		}
		if(!Space&&!player.dead)
		{
			if(Right)
			{
				dir = true;
				flip = SDL_FLIP_NONE;

			}
			if(Left)
			{
				dir = false;
				flip = SDL_FLIP_HORIZONTAL;

			}
		}
		if(dir)
		{
			dst.x = player.getX()+8- camera.x;
		}
		else
		{
			dst.x = player.getX()-2- camera.x;
		}
		timer1.Update(DeltaTime);

		dst.y = player.getY()+18-camera.y;
		if(timer1.Time>100)
		{
			timer1.Stop();
		}
		if(Space&&timer1.Time == 0)
		{
			for(int i = 0; i<bullets;i++)
			{
				if(*(bulletX+i) == -1)
				{
					timer1.Start();
					if(flip == SDL_FLIP_HORIZONTAL)
					{
						*(bulletX+i) = player.getX();
					}
					else
						*(bulletX+i) = player.getX()+32;
					*(bulletY+i) = player.getY()+20;
					if(dir)
						*(velX+i) = 0.7;
					else
						*(velX+i) = -0.7;
					*(velY+i) = (rand()%1000 - 500)/20000.0;
					break;
				}
			}
		}
		for(int i = 0; i<bullets;i++)
		{
			if(*(bulletX+i) != -1)
			{
				*(bulletX+i)+=*(velX+i)*DeltaTime;
				*(bulletY+i)+=*(velY+i)*DeltaTime;
			}
			if(*(bulletX+i) <0 ||*(bulletX+i)> map->getCols() *40)
			{
				*(bulletX+i) = -1;
			}
			if(1<<map->GetValue(*(bulletX+i)/40,*(bulletY+i)/40) & group1 || 1<<map->GetValue(*(bulletX+i)/40,(*(bulletY+i)+10)/40) == group1)
			{
				*(bulletX+i) = -1;
			}
		}
		//hit enemy
		for(vector<Enemy*>::iterator it = Enemies.begin(); it != Enemies.end();)
		{
			bool isdel = false;
			for(int i = 0; i<bullets;i++)
			{
				if(bulletX[i] != -1)
				{
					int res = (*it)->hit(bulletX[i],bulletY[i],5,1);
					if(res > 0)
					{
						bulletX[i] = -1;

					}
					if(res == 2)
					{
						delete (*it);
						it = Enemies.erase(it);
						isdel = true;
						break;

					}
				}
			}
			if(!isdel)
			{
				++it;
			}
		}
	}

	void Draw()
	{
		SDL_Rect bullRect;
		bullRect.x = 0;
		bullRect.y = 0;
		bullRect.h = 10;
		bullRect.w = 10;

		SDL_RenderCopyEx(renderer, gunSprite,NULL,&dst,0.0,NULL,flip);
		for(int i = 0; i<bullets;i++)
		{
			if(*(bulletX+i) != -1)
			{
				bullRect.x = *(bulletX+i)- camera.x;
				bullRect.y = *(bulletY+i)-camera.y;
				SDL_RenderCopy(renderer, bullet,NULL,&bullRect);
			}
		}
	}

	~Weapon(void)
	{
		delete []bulletX; delete []bulletY; delete velX; delete velY;
		SDL_DestroyTexture(gunSprite); SDL_DestroyTexture(bullet);
	}
};
