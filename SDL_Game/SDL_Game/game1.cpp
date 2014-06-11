#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

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
int OldMouse = 0;
//player
int playerX = 100;
int playerY = 100;
//keys
bool Up,Down,Left,Right;

//classes
#include "Map.h"
#include "Initialisation.h"
#include "IOcontrol.h"
#include "ImgLoader.h"
#include "gTimer.h"
#include "gButton.h"
#include "Player.h"
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
SDL_Texture* TestoverBtn = NULL;
SDL_Texture* TestdownBtn = NULL;
gButton* TestGB = NULL;
SDL_Texture* quitTex = NULL;
gButton* quitBtn = NULL;
//io stuff
bool quit = false;
SDL_Event e;

SDL_Rect pos;

Map* map1;
vector<SDL_Texture*> tiles;

Player* player;

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

	TestBtn = loader.loadTexturePNG("buttons/testbtn.png");
	TestoverBtn = loader.loadTexturePNG("buttons/testoverbtn.png");
	TestdownBtn = loader.loadTexturePNG("buttons/testdownbtn.png");
	TextureVect.push_back(TestBtn);
	TextureVect.push_back(TestoverBtn);
	TextureVect.push_back(TestdownBtn);
	int w = 0;
	int h = 0;
	SDL_QueryTexture(TestBtn,NULL,NULL,&w,&h);
	TestGB = new gButton((SCREEN_WIDTH - w)/2,100,w,h,TestBtn,TestoverBtn,TestdownBtn);

	quitTex = loader.loadTexturePNG("buttons/quitbtn.png");
	TextureVect.push_back(quitTex);
	w = 0;
	h = 0;
	SDL_QueryTexture(quitTex,NULL,NULL,&w,&h);
	quitBtn = new gButton((SCREEN_WIDTH - w)/2,300,w,h,quitTex);

	pos.x=SCREEN_WIDTH/2 - 150;
	pos.y=SCREEN_HEIGHT/2 -150;
	pos.w=300;
	pos.h = 300;
	
	SDL_Texture* tile1 = loader.loadTexturePNG("tiles/footile.png");
	SDL_Texture* tile2 = loader.loadTexturePNG("tiles/glasstile.png");
	
	tiles.push_back(tile1);
	tiles.push_back(tile2);
	map1 = loader.initMap(map1,"maps/map1.txt",tiles);

	player = new Player(80,80,loader.loadTexturePNG("sprites/player.png"));

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
		if(TestGB->Pressed(mouseX,mouseY))
		{
			state = Game;
		}
		if(quitBtn->Pressed(mouseX,mouseY))
		{
			quit = true;
		}

	}
	if(state == Game)
	{
		player->Update(map1);
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
	if(state == Game)
	{
		player->Draw();
		map1->Draw();
	}
}