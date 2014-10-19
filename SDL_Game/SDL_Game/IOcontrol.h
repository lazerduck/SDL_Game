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
				if(e->key.keysym.sym == SDLK_LEFT||e->key.keysym.sym == SDLK_a )
				{
					Left = true;
				}

				if(e->key.keysym.sym == SDLK_RIGHT||e->key.keysym.sym == SDLK_d)
				{
					Right = true;
				}


				if(e->key.keysym.sym == SDLK_UP||e->key.keysym.sym == SDLK_w)
				{
					Up = true;
				}


				if(e->key.keysym.sym == SDLK_DOWN||e->key.keysym.sym == SDLK_s)
				{
					Down = true;
				}
				if(e->key.keysym.sym == SDLK_SPACE)
				{
					Space = true;
				}
				if(e->key.keysym.sym == SDLK_ESCAPE)
				{
					Esc = true;
				}

				//Handle backspace
				if( e->key.keysym.sym == SDLK_BACKSPACE && input.length() > 0 )
				{
					//lop off character
					input.pop_back();
					updateinput = true;
				}
				//Handle copy
				else if( e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
				{
					SDL_SetClipboardText( input.c_str() );
					updateinput = true;
				}
				//Handle paste
				else if( e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
				{
					input = SDL_GetClipboardText();
					updateinput = true;
				}
				//tiles swaps Ground_T, Grass_T, Glass_T, Spike_T, Enemy_T, Mine_T, Turret_T
				if(e->key.keysym.sym == SDLK_1)
				{
					tile = Ground_T;
				}
				if(e->key.keysym.sym == SDLK_2)
				{
					tile = Grass_T;
				}
				if(e->key.keysym.sym == SDLK_3)
				{
					tile = Glass_T;
				}
				if(e->key.keysym.sym == SDLK_4)
				{
					tile = Spike_T;
				}
				if(e->key.keysym.sym == SDLK_5)
				{
					tile = Enemy_T;
				}
				if(e->key.keysym.sym == SDLK_6)
				{
					tile = Mine_T;
				}
				if(e->key.keysym.sym == SDLK_7)
				{
					tile = Turret_T;
				}
				if(e->key.keysym.sym == SDLK_0)
				{
					tile = Empty_T;
				}
			}
			if(e->type == SDL_KEYUP)
			{
				if(e->key.keysym.sym == SDLK_LEFT||e->key.keysym.sym == SDLK_a)
				{
					Left = false;
				}

				if(e->key.keysym.sym == SDLK_RIGHT||e->key.keysym.sym == SDLK_d)
				{
					Right = false;
				}


				if(e->key.keysym.sym == SDLK_UP||e->key.keysym.sym == SDLK_w)
				{
					Up = false;
				}
				if(e->key.keysym.sym == SDLK_DOWN||e->key.keysym.sym == SDLK_s)
				{
					Down = false;
				}
				if(e->key.keysym.sym == SDLK_SPACE)
				{
					Space = false;
				}
				if(e->key.keysym.sym == SDLK_ESCAPE)
				{
					Esc = false;
				}
			}
			if( e->type == SDL_KEYDOWN )
			{
				
			}
			//Special text input event
			else if( e->type == SDL_TEXTINPUT )
			{
				//Not copy or pasting
				if( !( ( e->text.text[ 0 ] == 'c' || e->text.text[ 0 ] == 'C' ) && ( e->text.text[ 0 ] == 'v' || e->text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
				{
					//Append character
					input += e->text.text;
					updateinput = true;
				}
			}
		}
		return false;
	}

};

