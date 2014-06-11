#pragma once
class IOcontrol
{
public:

	IOcontrol(void)
	{
	}

	~IOcontrol(void)
	{
	}

	bool quit(SDL_Event* e)
	{
		if(MouseState != SDL_MOUSEMOTION)
		{
			OldMouse = MouseState;
		}
		MouseState = SDL_GetMouseState(&mouseX,&mouseY);
		if(MouseState == SDL_MOUSEMOTION)
		{
			MouseState = OldMouse;
		}
		while(SDL_PollEvent(e) != 0)
		{
			//user requests to quit
			if(e->type == SDL_QUIT)
			{
				return true;
			}
			if(e->type == SDL_KEYDOWN)
			{
				if(e->key.keysym.sym == SDLK_LEFT)
				{
					Left = true;
				}

				if(e->key.keysym.sym == SDLK_RIGHT)
				{
					Right = true;
				}


				if(e->key.keysym.sym == SDLK_UP)
				{
					Up = true;
				}


				if(e->key.keysym.sym == SDLK_DOWN)
				{
					Down = true;
				}
			}
			if(e->type == SDL_KEYUP)
			{
				if(e->key.keysym.sym == SDLK_LEFT)
				{
					Left = false;
				}

				if(e->key.keysym.sym == SDLK_RIGHT)
				{
					Right = false;
				}


				if(e->key.keysym.sym == SDLK_UP)
				{
					Up = false;
				}


				if(e->key.keysym.sym == SDLK_DOWN)
				{
					Down = false;
				}
			}
		}
		return false;
	}

};

