#pragma once
class Camera
{
public:
	int x;
	float y;
	SDL_Rect view;
	Camera(void)
	{
		x = 0;
		y = 0;
		view.x = x;
		view.y = y;
		view.w = SCREEN_WIDTH/scalex;
		view.h = SCREEN_HEIGHT/scaley;
	}
	void Update(int playerx, int playery, int rows, int cols)
	{
		//set the camera x
		if(playerx > (SCREEN_WIDTH/scalex)/2&&playerx < cols*40-(SCREEN_WIDTH/scalex)/2)
		{
			x = (float)(playerx-(float)((float)SCREEN_WIDTH/scalex)/2);
		}
		else if(playerx < (SCREEN_WIDTH/scalex)/2)
		{
			x = 0;
		}
		else if(playerx > cols*40-(SCREEN_WIDTH/scalex)/2)
		{
			x = cols*40-(SCREEN_WIDTH/scalex);
		}
		//set the camera y
		if(playery > (SCREEN_HEIGHT/scaley)/2&&playery < rows*40-(SCREEN_HEIGHT/scaley)/2)
		{
			y = (float)playery-((float)SCREEN_HEIGHT/scaley)/2;
		}
		else if(playery < (SCREEN_HEIGHT/scaley)/2)
		{
			y = 0;
		}
		else if(playery > rows*40-(SCREEN_HEIGHT/scaley)/2)
		{
			y = rows*40-(SCREEN_HEIGHT/scaley);
		}
		view.x = x;
		view.y = y;
	}

	void Update(int playerx, int playery, int rows, int cols, bool editor)
	{
		//set the camera x
		if(playerx > (SCREEN_WIDTH/scalex)/2&&playerx < cols*40-(SCREEN_WIDTH/scalex)/2)
		{
			x = (float)(playerx-(float)((float)SCREEN_WIDTH/scalex)/2);
		}
		else if(playerx < (SCREEN_WIDTH/scalex)/2)
		{
			x = 0;
		}
		else if(playerx > cols*40-(SCREEN_WIDTH/scalex)/2)
		{
			x = cols*40-(SCREEN_WIDTH/scalex);
		}
		//set the camera y
		if(playery > (0)&&playery < rows*40-(SCREEN_HEIGHT/scaley)/2)
		{
			y = (float)playery-((float)SCREEN_HEIGHT/scaley)/2;
		}

		else if(playery > rows*40-(SCREEN_HEIGHT/scaley)/2)
		{
			y = rows*40-(SCREEN_HEIGHT/scaley);
		}
		view.x = x;
		view.y = y;
	}

	~Camera(void)
	{
	}
};

