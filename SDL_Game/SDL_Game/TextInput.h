#pragma once
class TextInput
{
private:
	SDL_Texture* TextTex;
	SDL_Rect dst;
	int Max;
	int Font;
	DrawRect* rect;
	bool active,prev;
	SDL_Color col;
public:
	string text;

	TextInput(void)
	{
	}

	TextInput(int x, int y, int charmax, int font)
	{
		Max = charmax;
		Font = font;
		dst.x = x;
		dst.y = y;
		dst.h  = 50;
		dst.w = 200;
		active = false;
		prev = false;
		rect = new DrawRect(dst.x,dst.y,dst.h,dst.w);
		col.a = 0x00;
		col.r = 0x00;
		col.g = 0x00;
		col.b = 0x00;
		TextTex = TextCreator.CreateText("test",col);
	}

	bool hit(int x, int y)
	{
		bool hit = true;
		if(x>rect->area.x*scalex + rect->area.w*scalex)
		{
			hit = false;
		}
		if(x<rect->area.x*scalex)
		{
			hit = false;
		}
		if(y>rect->area.y*scaley + rect->area.h*scaley)
		{
			hit = false;
		}
		if(y<rect->area.y*scaley)
		{
			hit = false;
		}
		return hit;
	}

	void Update()
	{
		if(MouseState == SDL_BUTTON(1))
		{
			if(hit(mouseX,mouseY))
			{
				active = true;
			}
			else
			{
				active = false;
			}
		}

		if(prev == false &&active == true)
		{
			input = text;
		}
		if(active)
		{
			text = input;
			if(updateinput == true)
			{
				SDL_DestroyTexture(TextTex);
				TextTex = TextCreator.CreateText(text,col);
				SDL_QueryTexture(TextTex,NULL,NULL, &dst.w,&dst.h);
				while(rect->area.w < dst.w)
				{
					input.pop_back();
					text.pop_back();
					TextTex = TextCreator.CreateText(text,col);
					SDL_QueryTexture(TextTex,NULL,NULL, &dst.w,&dst.h);
				}
				updateinput = false;
			}

		}
		prev = active;
	}

	void Draw()
	{
		rect->Draw();
		SDL_RenderCopy(renderer,TextTex,NULL,&dst);
	}
	~TextInput(void)
	{
		delete rect;
	}
};

