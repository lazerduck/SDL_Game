#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum State {Splash,MainMenu,Game};
State state;

//The window
SDL_Window* window = NULL;
//The surface
SDL_Surface* screenSurface = NULL;

//hardware accellerated
SDL_Renderer* renderer = NULL;

//delta time
float DeltaTime = 0;
float PrevTicks = 0;

//mouse
int mouseX = 0;
int mouseY = 0;
int MouseState = 0;
//classes
#include "Initialisation.h"
#include "IOcontrol.h"
#include "ImgLoader.h"
#include "gTimer.h"
#include "gButton.h"
//timers
gTimer* T1 = NULL;

vector<gTimer*> Timers;
//main functions
void Update();
void Draw();
void Initialise();
//classes
IOcontrol io;
ImgLoader loader;
//variables splash
SDL_Texture* texture = NULL;
vector<SDL_Texture*> TextureVect;
//varibles main
SDL_Texture* TestBtn = NULL;
gButton* TestGB = NULL;
SDL_Texture* quitTex = NULL;
gButton* quitBtn = NULL;
//io stuff
bool quit = false;
SDL_Event e;

SDL_Rect pos;

int main( int argc, char* args[] )
{
	bool success = true;
	//initialiser
	Initialisation init;
	

	success = init.start();


	Initialise();
	if(success)
	{	
		int counted = 0;
		float start = SDL_GetTicks();
		//set initial game state
		state = Splash;

		//<game loop>
		while(!quit)
		{
			//get framrate
			if(SDL_GetTicks() - start > 1000)
			{
				printf("fps: %d\n", counted);
				counted = 0;
				start = SDL_GetTicks();
			}
			//get deltatime
			DeltaTime = SDL_GetTicks() - PrevTicks;
			PrevTicks = SDL_GetTicks();
			
			 SDL_RenderClear( renderer );
			 //timer update
			 for(vector<gTimer*>::iterator it = Timers.begin(); it!= Timers.end(); ++it)
			 {
				 (*it)->Update(DeltaTime);
			 }

			 Update();

			 Draw();

			SDL_RenderPresent(renderer);
			++counted;
		}
		//<\game loop>
	}
	init.DeleteTextures(TextureVect);
	init.Exit(window,screenSurface);
	return 0;
}

void Initialise()
{
	T1 = new gTimer;
	Timers.push_back(T1);

	texture = loader.loadTexturePNG("helloworld.png");
	TextureVect.push_back(texture);

	TestBtn = loader.loadTexturePNG("testbtn.png");
	TextureVect.push_back(TestBtn);
	int w = 0;
	int h = 0;
	SDL_QueryTexture(TestBtn,NULL,NULL,&w,&h);
	TestGB = new gButton((SCREEN_WIDTH - w)/2,100,w,h,TestBtn);

	quitTex = loader.loadTexturePNG("quitbtn.png");
	TextureVect.push_back(quitTex);
	w = 0;
	h = 0;
	SDL_QueryTexture(quitTex,NULL,NULL,&w,&h);
	quitBtn = new gButton((SCREEN_WIDTH - w)/2,300,w,h,quitTex);

	pos.x=SCREEN_WIDTH/2 - 150;
	pos.y=SCREEN_HEIGHT/2 -150;
	pos.w=300;
	pos.h = 300;
}

void Update()
{
	//update timers

	quit = io.quit(&e);

	if(state ==Splash)
	{
		T1->Start();
		if(T1->Time > 3000)
		{
			T1->Stop();
			state = MainMenu;
		}
	}
	if(state == MainMenu)
	{
		if(MouseState == SDL_BUTTON(1))
		{
			if(TestGB->hit(mouseX,mouseY))
			{
				state = Splash;
			}
			if(quitBtn->hit(mouseX,mouseY))
			{
				quit = true;
			}
		}
	}
}

void Draw()
{
	if(state == Splash)
	{
		SDL_RenderCopy(renderer,texture,NULL,&pos);
	}
	if(state == MainMenu)
	{
		TestGB->Draw();
		quitBtn->Draw();
	}
}