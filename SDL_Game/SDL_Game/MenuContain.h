#pragma once
class MenuContain
{
private:
	//gbutton container
	vector<gButton*> ButtonCont;
public:

	MenuContain(void)
	{
	}

	void Update(bool& quit)
	{

	}
	bool isPressed(string name)
	{
		for(vector<gButton*>::iterator it = ButtonCont.begin(); it != ButtonCont.end();++it)
		{

			if((*it)->getName() == name)
			{
				if((*it)->Pressed())
				{
					return true;
				}
				else
				{
					return false;
				}
			}

		}
	}
	//(SCREEN_WIDTH-w)/(3*scalex),100,w,h,NewGame,true
	bool addButton(SDL_Texture* texture, int xPos, int yPos, int width, int height, string name)
	{

		gButton *temp = new gButton(xPos,yPos,width,height,texture,true,name);
		ButtonCont.push_back(temp);
		return true;

	}

	void Draw()
	{
		for(vector<gButton*>::iterator it = ButtonCont.begin(); it != ButtonCont.end();++it)
		{
			(*it)->Draw();
		}
	}

	~MenuContain(void)
	{
		for(vector<gButton*>::iterator it = ButtonCont.begin(); it != ButtonCont.end();++it)
		{
			delete(*it);
		}
		ButtonCont.clear();
	}
};

