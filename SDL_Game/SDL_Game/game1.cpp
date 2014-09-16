#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
float scalex = 1.2;
float scaley = 1.2;

//Screen dimension constants
const int SCREEN_WIDTH = 854;
const int SCREEN_HEIGHT = 480;

int MIDX = 640;
int MIDY = 360;

enum State {Splash,MainMenu,Game,GameOver};
State state;

enum Tiles {Empty_T, Ground_T, Grass_T, Glass_T, Spike_T, Enemy_T, Mine_T, Turret_T};
static const unsigned group1 = (1<<Ground_T)|(1<<Grass_T)|(1<<Spike_T);
static const unsigned group2 = (1<<Empty_T)|(1<<Glass_T);

//The window
SDL_Window* window = NULL;
//The surface
SDL_Surface* screenSurface = NULL;

//hardware accellerated
SDL_Renderer* renderer = NULL;

//delta time
float DeltaTime = 0;
float PrevTicks = 0;
float slowTime = 1;

//mouse
int mouseX = 0;
int mouseY = 0;
int MouseState = 0;
int OldMouse = 0;
//player
int playerX = 100;
int playerY = 100;
//keys
bool Up,Down,Left,Right,Space;
//camera
#include "Camera.h"
Camera camera;
#include "TextCont.h"
TextCont TextCreator;

//classes
#include "Map.h"
#include "Initialisation.h"
#include "IOcontrol.h"
#include "ImgLoader.h"
#include "gTimer.h"
#include "gButton.h"
#include "Player.h"
#include "Blast.h"
vector<Blast*> Blasts;
//enemies
#include "Enemy.h"
#include "Sad_onion.h"
#include "Mine.h"
#include "Turret.h"
//menu
#include "MenuContain.h"
//hud
#include "Hud.h"
Hud* hud;

//enemy holder
vector<Enemy*> Enemies;


#include "Weapon.h"

//timers
gTimer* T1 = NULL;
gTimer* T2 = NULL;

vector<gTimer*> Timers;
//weapon
Weapon* weapon;
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

//io stuff
bool quit = false;
SDL_Event e;

SDL_Rect pos;

Map* map1;
vector<SDL_Texture*> tiles;

Player* player;

MenuContain* Main;


//todo
//bullett hit effect -- [Done] - enemies flicker when hit particle effects may still be nessecary
//enemies
//-flying
//-mines -- [Done] - Explode and blast affect other mines and player
//-spikes -- [Done] - spikes and new map improvements as well as load area
//-turrets -- [Progress] - base of turret done
//take damage -- [Done] - use loop in main game to get around refences
//sprites
//-enemy
//-weapons
//-powerups
//-hud -- [Progress] - health bar and text
//-menu -- [Progress] - buttons and method updated - need graphics
//-level blocks
//-particles
//levels
//weapons
//animation
//-running -- [Progress] - animation with running - needs strafing and jumping maybe damage
//-jumping
//-taking damage
//-idling
//hud
//save?
//power ups
//story -- [Progress] - few levels planed, synopsis and intro
//text -- [Finished] text textures can now be created using the TextCreator class - may need work for different font sizes as only 38p is initialised
//Enemy shooting
//hold to jump higher -- [Finished] - timer allows you to jump at different heights

//bugs
//left jump + space dont work together as well as being clunky -- [Fixed] - need to use wasd and space to prevent key conflict unique to laptop
//stuttering -- [Fixed] - turned on vsync - moved camera update in to the player
//getting stuck in floor when falling -- [Fixed] - loop to move back up may slow performance although only about 10 loops - now calculated w/o loop
//texture wrap around -- [Fixed] - mis-diagnosed vsync tear
//buttons dont move with the camera -- [Fixed] - multiplied by scalex/y
//multiple bullets at a time -- [Fixed] - lowering the frame rate seemed to fix this
//issue causing left and right corrections to be done before up and down causing stutter then landing -- [Fixed] - check behind when landing in motion
//wall jumping glitch -- [Fixed] - move first then check for collisions and correct
//memory leaks -- [Fixed] - remeber to delete objects migh need improving for ease vectors work well
//dont render off screen tiles or enemies -- [Fixed] - not worth time for enemies, but tiles done
//anti-ailiasing -- [Fixed] - game has a type of pixel sampling, requires larger textures to be accurate
//all enemies blink when 1 is shot -- [Fixed] - changes the texture and then reverts, may need to create 2 textures if speed gets too low
//catch head when collide with roof -- [Fixed] - check roof collision first
//bullet wall hittest depends on top left corner and not hitbox -- [Fixed] - check bottom of bullet as well
//memory leak on hud -- [Fixed] - defining char* s with a new and then replacing it with itoa caused issues, using stringstream
//odd memory leaks unknown cause -- [Fixed] - didn't delete the object before erasing it
//enemy doesnt cause damage -- [Fixed] - inaccurate collision detection, now improved, improve bullet as well
//2 hits at the same time -- [Fixed] - only take damage if not "hit"
//texture leaks? no evidence so far but should happen -- [Fixed] - was actually not deleting mine blasts which out lasted the thread

int main( int argc, char* args[] )
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	bool success = true;
	//initialiser
	Initialisation init;
	camera.y = 40;
	
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
			DeltaTime = (SDL_GetTicks() - PrevTicks)/slowTime;
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
	//delete main menu
	delete Main;
	//delete map
	delete map1;
	//delete player
	delete player;
	delete weapon;
	//delete timers
	for(vector<gTimer*>::iterator it = Timers.begin(); it != Timers.end(); ++it)
	{
		delete *it;
	}
	//delete enemies Enemies
	for(vector<Enemy*>::iterator it = Enemies.begin(); it != Enemies.end(); ++it)
	{
		delete *it;
	}
	for(vector<Blast*>::iterator it = Blasts.begin(); it != Blasts.end();++it)
	{
		delete *it;
	}
	//delete hud
	delete hud;

	init.DeleteTextures(TextureVect);
	init.Exit(window,screenSurface);
	return 0;
}

void Initialise()
{
	T1 = new gTimer;
	T2 = new gTimer;
	Timers.push_back(T1);
	Timers.push_back(T2);

	texture = loader.loadTexturePNG("helloworld.png");
	TextureVect.push_back(texture);

	pos.x=SCREEN_WIDTH/2 - 150;
	pos.y=SCREEN_HEIGHT/2 -150;
	pos.w=300;
	pos.h = 300;
	
	SDL_Texture* tile1 = loader.loadTexturePNG("tiles/footile.png");
	SDL_Texture* tile2 = loader.loadTexturePNG("tiles/dirtgrass.png");
	SDL_Texture* tile3 = loader.loadTexturePNG("tiles/glasstile.png");
	SDL_Texture* tile4 = loader.loadTexturePNG("tiles/Spikes.png");
	SDL_Texture* enemy1 = loader.loadTexturePNG("sprites/sad_onion.png");

	TextureVect.push_back(enemy1);
	
	tiles.push_back(tile1);
	tiles.push_back(tile2);
	tiles.push_back(tile3);
	tiles.push_back(tile4);

	player = new Player(80,800,loader.loadTexturePNG("sprites/ashen1.png"));
	hud = new Hud(loader.loadTexturePNG("sprites/HealthBlock.png"));
	weapon = new Weapon(loader.loadTexturePNG("sprites/pistol.png"),loader.loadTexturePNG("sprites/bullet.png"),*player);


	Main = new MenuContain(loader);
}

void Update()
{
	//update timers

	quit = io.quit(&e);

	if(state ==Splash)
	{
		T1->Start();
		if(T1->Time >2000)
		{
			T1->Stop();
			state = MainMenu;
		}
	}
	if(state == MainMenu)
	{
		Main->Update(quit);
		if(state == Game)
		{
			map1 = loader.initMap(map1,"maps/map1.txt",tiles);
			SDL_Texture* enemy1 = loader.loadTexturePNG("sprites/sad_onion.png");
			SDL_Texture* Minetex = loader.loadTexturePNG("sprites/Mine.png");
			SDL_Texture* Boom = loader.loadTexturePNG("Sprites/mineblast.png");
			SDL_Texture* turret_tex = loader.loadTexturePNG("Sprites/turret_base.png");
			SDL_Texture* turret_gun = loader.loadTexturePNG("Sprites/turret_gun.png");
			for(int i = 0;i<map1->getRows();i++)
			{
				for(int j = 0; j<map1->getCols();j++)
				{
					if(map1->GetValue(i,j) == Enemy_T)
					{
						map1->setValue(i,j,0);
						Sad_onion *enemyinst = new Sad_onion(enemy1,i,j);
						Enemies.push_back(enemyinst);
					}
					if(map1->GetValue(i,j) == Mine_T)
					{
						map1->setValue(i,j,0);
						Mine *mineinst = new Mine(Minetex,Boom,i,j);
						Enemies.push_back(mineinst);
					}
					if(map1->GetValue(i,j) ==Turret_T)
					{
						map1->setValue(i,j,0);
						Turret *turinst = new Turret(turret_tex,turret_gun,i,j);
						Enemies.push_back(turinst);
					}
				}
			}
		}
	}
	if(state == Game)
	{
		player->Update(map1);
		hud->Update(player);
		weapon->Update(*player,map1);
		for(vector<Enemy*>::iterator it = Enemies.begin(); it != Enemies.end();)
		{
			bool isdel = false;
			(*it)->Update(player,map1);
			if(!player->dead);
			{
				if((*it)->hit(player->getRect(),0) !=0)
				{
					player->Damage((*it)->damage);
				}
			}
			if((*it)->getHealth() == 0)
			{
				delete (*it);
				it = Enemies.erase(it);
				isdel = true;
			}
			if(!isdel)
			{
				++it;
			}
		}
		for(vector<Blast*>::iterator it = Blasts.begin(); it != Blasts.end();)
		{
			//hittest player
			if(player->CircleCollide((*it)->getX(),(*it)->getY(),(*it)->getR()))
			{
				player->Damage(30);
			}

			bool isdel = false;
			(*it)->Update();
			if((*it)->dead)
			{
				isdel = true;
				delete (*it);
				it = Blasts.erase(it);
			}
			if(!isdel)
			{
				++it;
			}
		}
		if(player->dead)
		{
			T2->Start();
			if(T2->Time > 1600)
			{
				state = GameOver;
				slowTime = 1;
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
		Main->Draw();
	}
	if(state == Game)
	{		
		player->Draw();
		weapon->Draw();
		map1->Draw();
		for(vector<Enemy*>::iterator it = Enemies.begin(); it != Enemies.end();++it)
		{
			(*it)->Draw();
		}
		for(vector<Blast*>::iterator it = Blasts.begin(); it != Blasts.end();++it)
		{
			(*it)->Draw();
		}
		hud->Draw();
	}
}