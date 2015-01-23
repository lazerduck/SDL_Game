#pragma once
class Particle
{
private:
	float *xArr;
	float *yArr;
	float *xVel;
	float *yVel;
	float *life;

	int size;
public:

	Particle(void)
	{
		size = 1000;
		xArr = new float[size];
		yArr = new float[size];
		xVel = new float[size];
		yVel = new float[size];
		life = new float[size];
		
		for(int i = 0; i<size; i++)
		{
			xArr[i] = -1;
			yArr[i] = 0;
			xVel[i] = 0;
			yVel[i] = 0;
			life[i] = 0;
		}
	}

	void Update(Map* map)
	{ 
		for(int i  = 0; i<size;i++)
		{
			if(xArr[i] != -1)
			{
				xArr[i] += xVel[i]*DeltaTime;
				yArr[i] += yVel[i]*DeltaTime;
				yVel[i] +=0.05;
				life[i] -= DeltaTime;
				if(1<<map->GetValue(*(xArr+i)/40,(*(yArr+i)+yVel[i]*DeltaTime)/40) & group1 || 1<<map->GetValue(*(xArr+i)/40,(*(yArr+i)-yVel[i]*DeltaTime)/40) & group1)
			    {
					yVel[i] = -yVel[i];
					yArr[i] += yVel[i];
				}
				if(1<<map->GetValue((*(xArr+i)+xVel[i]*DeltaTime)/40,*(yArr+i)/40) & group1 || 1<<map->GetValue((*(xArr+i)-xVel[i]*DeltaTime)/40,*(yArr+i)/40) & group1)
			    {
					xVel[i] = -xVel[i];
					xArr[i] += xVel[i]*2;
				}
				
								if(life[i] <=0)
				{
					xArr[i] = -1;
				}
			}
		}
	}

	void Draw()
	{
		SDL_Rect rect;
		rect.h = 10;
		rect.w = 10;
		SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0x0F );
		for(int i = 0; i < size; i++)
		{
			if(xArr[i]!=-1)
			{
				rect.x = (int)xArr[i] - camera.x;
				rect.y = (int)yArr[i] - camera.y;
				SDL_RenderFillRect(renderer,&rect);
			}
		}
	}

	void Create(int x, int y, float xvel, float yvel, float Life)
	{
		for(int i = 0; i < size; i++)
		{
			if(xArr[i] == -1)
			{
				xArr[i] = x;
				yArr[i] = y;
				xVel[i] = xvel;
				yVel[i] = yvel;
				life[i] = Life;
				return;
			}
		}
	}

	~Particle(void)
	{
	}
};

