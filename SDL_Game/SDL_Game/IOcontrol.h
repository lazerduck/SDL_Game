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
		}
		return false;
	}

};

