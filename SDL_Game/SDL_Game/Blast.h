#pragma once
class Blast
{
private:
	int cX, cY;
	SDL_Texture* texture;
	float radius;
	SDL_Rect dst;
	gTimer tim;
public:
	bool dead;
	Blast(void)
	{
	}

	Blast(SDL_Texture* tex, int centX, int centY)
	{
		dead = false;
		texture = tex;
		cX = centX;
		cY = centY;
		radius = 20;
		dst.x = centX -radius -camera.x;
		dst.y = centY - radius - camera.y;
		dst.w = 2*radius;
		dst.h = dst.w;
		tim.Start();
		SDL_SetTextureAlphaMod( texture, 0x40 );
	}

	void Update()
	{
		tim.Update(DeltaTime);
		radius += 0.11*DeltaTime;
		dst.x = cX -radius -camera.x;
		dst.y = cY - radius - camera.y;
		dst.w = 2*radius;
		dst.h = dst.w;
		if(tim.Time > 500)
		{
			dead= true;
		}
	}

	int getX()
	{
		return cX;
	}
	int getY()
	{
		return cY;
	}
	float getR()
	{
		return radius;
	}

	void Draw()
	{
		SDL_RenderCopy(renderer, texture,NULL,&dst);
	}

	~Blast(void)
	{
	}
};

