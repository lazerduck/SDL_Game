#pragma once
class Player
{
	float x;
	float y;

	SDL_Rect dst;

	SDL_Texture* Sprite;
public:

	Player(void)
	{
	}
	Player(int startX, int startY, SDL_Texture* sprite)
	{
		x = startX;
		y = startY;
		Sprite = sprite;
		playerX = (int)x+SCREEN_WIDTH/2;
		playerY = (int)y+SCREEN_HEIGHT/2;
	}

	~Player(void)
	{
		SDL_DestroyTexture(Sprite);
	}
};

