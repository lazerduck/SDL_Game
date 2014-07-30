#pragma once
class Camera
{
public:
	int x;
	float y;
	Camera(void)
	{
		x = 0;
		y = 0;
	}
	void Update(int playerx, int playery, int rows, int cols)
	{
		//set the camera x
		if(playerx > (SCREEN_WIDTH/scalex)/2&&playerx < cols*40-(SCREEN_WIDTH/scalex)/2)
		{
			x = (float)(playerx-(float)((float)SCREEN_WIDTH/scalex)/2);
		}
		//set the cameray
		if(playery > (SCREEN_HEIGHT/scaley)/2&&playery < rows*40-(SCREEN_HEIGHT/scaley)/2)
		{
			y = (float)playery-((float)SCREEN_HEIGHT/scaley)/2;
		}
	}

	~Camera(void)
	{
	}
};

