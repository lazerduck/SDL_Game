#pragma once
class Hud
{
	int health;
	SDL_Rect healthRect;
	SDL_Texture* healthbar;
	SDL_Texture* healthText;
	SDL_Rect textRect;
	SDL_Color col;
public:

	Hud(void)
	{
		health = 0;
	}
	Hud(SDL_Texture* hb)
	{
		health = 0;
		healthRect.x = 5;
		healthRect.y = 20;
		healthRect.w = 10;
		healthRect.h = 15;
		healthbar = hb;
		textRect.x = 5;
		textRect.y = 1;
		
		textRect.h = 20;
		textRect.w =20;
		
		col.a = 0x00;
		col.r = 0x00;
		col.g = 0x00;
		col.b = 0x00;
		healthText = NULL;
	}
	void Update(Player* player)
	{ 
		if(health != player->getHealth())
		{
			health = player->getHealth();
			if(healthText != NULL)
			{
				SDL_DestroyTexture(healthText);
			}
			std::stringstream ss;
			ss<<health;
			string textstring = ss.str();
			textstring+="%";
			healthText = TextCreator.CreateText(textstring,col);
			SDL_QueryTexture(healthText,NULL,NULL,&textRect.w,&textRect.h);
			textRect.h /=2;
			textRect.w /=2;			
		}
	}

	void Draw()
	{
		for(int i = 0;i<health;i+=20)
		{
			healthRect.x = (i/2) + 3;
			SDL_RenderCopy(renderer,healthbar,NULL,&healthRect);
		}
		SDL_RenderCopy(renderer,healthText,NULL,&textRect);
	}

	~Hud(void)
	{
		SDL_DestroyTexture(healthbar);
		SDL_DestroyTexture(healthText);
	}
};

