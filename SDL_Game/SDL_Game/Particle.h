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
		size = 100;
		xArr = new float[size];
		yArr = new float[size];
		xVel = new float[size];
		yVel = new float[size];
		life = new float[size];
		
		for(int i = 0; i<100; i++)
		{
			xArr[i] = -1;
			yArr[i] = 0;
			xVel[i] = 0;
			yVel[i] = 0;
			life[i] = 0;
		}
	}

	void Update()
	{
		for(int i  = 0; i<size;i++)
		{
			if(xArr[i] != -1)
			{
				xArr[i] += xVel[i];
				yArr[i] += yVel[i];
				life[i] -= DeltaTime;
				if(life[i] <=0)
				{
					xArr[i] = -1;
				}

			}
		}
	}

	void Draw()
	{
		for(int i = 0; i < size; i++)
		{
			if(xArr[i]!=-1)
			{
				SDL_SetRenderDrawColor(renderer,1,1,1,255);
				SDL_RenderDrawPoint(renderer,(int)xArr[i]- camera.x,(int)yArr[i]-camera.y);
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

