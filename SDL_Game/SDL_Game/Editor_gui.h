#pragma once
class Editor_gui
{
private:
	SDL_Rect tileRect;
	SDL_Rect tileSelector;
	SDL_Rect tileselectrect;
	SDL_Texture* selectionRect;
	SDL_Texture* testLevel;
	SDL_Texture* saveLevel;
	SDL_Texture* exitLevel;
	gButton* saveBtn;
	gButton* testBtn;
	gButton* exitBtn;
	bool test;
	string MapAddress;
public:
	bool setPlayer;
	SDL_Rect startPos;
	Editor_gui(void)
	{

	}
	Editor_gui(SDL_Texture* selec, SDL_Texture* testTex, SDL_Texture* saveTex, SDL_Texture* exitTex)
	{
		startPos.h = 80;
		startPos.w = 40;

		selectionRect = selec;
		tileRect.h = 40;
		tileRect.w = 40;
		tileSelector.y = 5;
		tileSelector.h = 40;
		tileSelector.w = 40;
		tileselectrect.x = 5;
		tileselectrect.y = 5;
		tileselectrect.w = 40;
		tileselectrect.h = 40;
		saveLevel = saveTex;
		testLevel = testTex;
		exitLevel = exitTex;
		saveBtn = new gButton(380,5,100,40,saveLevel,true,"save");
		testBtn = new gButton(485,5,100,40,testLevel,true,"test");
		exitBtn = new gButton(590,5,100,40,exitLevel,true,"exit");
		test = false;
		setPlayer = false;
		MapAddress = "";
	}
	void Update()
	{
		int resy = ((mouseY/scaley)+camera.y)/40;
		int resx = (((mouseX)/scalex)+camera.x)/40;
		resy*=40;
		resx*=40;
		if(MouseState == 0 && OldMouse == SDL_BUTTON(1))
		{
			if((mouseX/scalex>startPos.x&&mouseX/scalex<startPos.x+startPos.w) && (mouseY/scaley>startPos.y&&mouseY/scaley<startPos.y+startPos.h))
			{
				if(map1->GetValue(resx/40,resy/40) == 0&&map1->GetValue(resx/40,(resy/40)+1)==0)
				{
				setPlayer = !setPlayer;
				}
			}
		}
		if(setPlayer)
		{
			playerStartX = resx;
			playerStartY = resy;
		}
		startPos.x = playerStartX - camera.x;
		startPos.y = playerStartY - camera.y;
		tileRect.x = resx -camera.x;
		tileRect.y = resy- camera.y;

		tileselectrect.x = 5 + (45*(tile-1));
		if(tile == 0)
		{
			tileselectrect.x = 5 + (45*7);
		}
		tileSelector.x = 5;
		if(saveBtn->Pressed())
		{
			map1->save();
		}
		if(testBtn->Pressed())
		{
			test = true;
			map1->save();
		}
		if(exitBtn->Pressed())
		{
			state = LevelEdit;
		}

	}
	void Draw()
	{
		SDL_RenderCopy(renderer, selectionRect,NULL,&tileRect);
		for(vector<SDL_Texture*>::iterator it = tiles.begin(); it!=tiles.end();++it)
		{
			SDL_RenderCopy(renderer, *it,NULL,&tileSelector);
			tileSelector.x += 45;
		}
		SDL_RenderCopy(renderer, playerSprite,NULL,&startPos);
		SDL_RenderCopy(renderer, selectionRect,NULL,&tileselectrect);
		saveBtn->Draw();
		testBtn->Draw();
		exitBtn->Draw();
	}
	bool StartTest()
	{
		return test;
	}
	void EndTest()
	{
		test = false;
	}
	void setMapAddress(string address)
	{
		MapAddress  = address;
	}
	string GetAddress()
	{
		return MapAddress;
	}

	~Editor_gui(void)
	{
		delete saveBtn;
		delete testBtn;
		delete exitBtn;
	}
};

