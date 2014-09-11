#pragma once
class MenuContain
{
private:
	SDL_Texture* Background;
	SDL_Rect BackRect;
	SDL_Texture* Foreground;
	SDL_Rect ForeRect;
	SDL_Texture* NewGame;
	SDL_Texture* Exit;
	SDL_Texture* TextTest;
	SDL_Rect TextRect;
	gButton* New_Game;
	gButton* Exit_Game;

public:

	MenuContain(void)
	{
	}
	MenuContain(ImgLoader loader)
	{
		Background = loader.loadTexturePNG("sprites/menu/sofa_720.png");
		Foreground = loader.loadTexturePNG("sprites/menu/camera.png");
		NewGame = loader.loadTexturePNG("sprites/menu/buttons/NewGame_btn.png");
		Exit = loader.loadTexturePNG("sprites/menu/buttons/Exit_btn.png");
		int w,h;
		SDL_QueryTexture(NewGame,NULL,NULL,&w,&h);
		w = w/3;
		New_Game = new gButton((SCREEN_WIDTH-w)/(3*scalex),100,w,h,NewGame,true);
		SDL_QueryTexture(Exit,NULL,NULL,&w,&h);
		Exit_Game = new gButton((SCREEN_WIDTH-w)/(3*scalex),200,w,h,Exit);
		BackRect.x = 0;
		BackRect.y = 0;
		BackRect.w = SCREEN_WIDTH/scalex;
		BackRect.h = SCREEN_HEIGHT/scaley;
		ForeRect.x = 350;
		ForeRect.y = 200;
		SDL_QueryTexture(Foreground,NULL,NULL,&ForeRect.w,&ForeRect.h);
		ForeRect.w /= 1.3*scalex;
		ForeRect.h /= 1.3*scaley;
		SDL_Color col;
		col.a = 0x00;
		col.r = 0x00;
		col.g = 0x00;
		col.b = 0x00;
		TextTest = TextCreator.CreateText("version: 0.1.2", col);
		TextRect.x = 0;
		TextRect.y = 0;
		SDL_QueryTexture(TextTest,NULL,NULL,&TextRect.w,&TextRect.h);
		TextRect.h = TextRect.h/2;
		TextRect.w = TextRect.w/2;
	}

	void Update(bool& quit)
	{

			if(	New_Game->Pressed())
			{
				state = Game;
			}
			if(Exit_Game->Pressed())
			{
				quit = true;
			}
		
	}

	void Draw()
	{
		SDL_RenderCopy(renderer,Background,NULL,&BackRect);
		SDL_RenderCopy(renderer,Foreground,NULL,&ForeRect);
		SDL_RenderCopy(renderer,TextTest,NULL,&TextRect);
		New_Game->Draw();
		Exit_Game->Draw();
	}

	~MenuContain(void)
	{
		SDL_DestroyTexture(Background);
		SDL_DestroyTexture(Foreground);
		delete New_Game;
		delete Exit_Game;
	}
};

