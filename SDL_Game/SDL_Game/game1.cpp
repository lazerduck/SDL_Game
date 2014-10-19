//map format
/*maprows mapcolumns playerstartx playerstarty
1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1 1 1 1*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vld.h> 

using namespace std;
float scalex = 1.2;
float scaley = 1.2;



//Screen dimension constants
const int SCREEN_WIDTH = 854;
const int SCREEN_HEIGHT = 480;

float leveleditx = 0;
float leveledity = 0;

int MIDX = 640;
int MIDY = 360;

enum State {Splash,MainMenu,Game,GameOver,Pause,LevelEdit,LevelEditPlay};
State state;

enum Tiles {Empty_T, Ground_T, Grass_T, Glass_T, Spike_T, Enemy_T, Mine_T, Turret_T};
Tiles tile;



static const unsigned group1 = (1<<Ground_T)|(1<<Grass_T)|(1<<Spike_T);
static const unsigned group2 = (1<<Empty_T)|(1<<Glass_T);


string bpath;

//input
string input;
bool updateinput = false;

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

//enemy bullets
int enemybull = 200;
float *posx = new float[enemybull];
float *posy = new float[enemybull];
float *velx = new float[enemybull];
float *vely = new float[enemybull];
SDL_Texture* enemyBullet;


//mouse
int mouseX = 0;
int mouseY = 0;
int MouseState = 0;
int OldMouse = 0;
//player
int playerStartX = 100;
int playerStartY = 100;
//keys
bool Up,Down,Left,Right,Space,Esc;
bool Escprev;
//camera
#include "Camera.h"
Camera camera;
#include "TextCont.h"
TextCont TextCreator;
#include "DrawRect.h"
#include "TextInput.h"

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
#include "Turret_gun.h"
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

void UpdateEnemyBull();
void DrawEnemyBull();

void loadLevel(string mapadd);
void loadLevelEditor(string mapadd);
//classes
IOcontrol io;
ImgLoader loader;

//load the textures

SDL_Texture* tile1;
SDL_Texture* tile2;
SDL_Texture* tile3;
SDL_Texture* tile4;
SDL_Texture* tile5;
SDL_Texture* tile6;
SDL_Texture* tile7;

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
MenuContain* PauseMenu;
MenuContain* EditMenu;

//main menu images
SDL_Texture* Foreground;
SDL_Texture* Background;
SDL_Texture* TextTest;

SDL_Rect BackRect;
SDL_Rect ForeRect;
SDL_Rect TextRect;

SDL_Color col;

//level editor
TextInput* Tinput;

SDL_Rect editorSelect;
DrawRect* menurect;

//todo
//bullett hit effect -- [Done] - enemies flicker when hit particle effects may still be nessecary
//enemies
//-flying
//-mines -- [Done] - Explode and blast affect other mines and player
//-spikes -- [Done] - spikes and new map improvements as well as load area
//-turrets -- [Done] - Hits player, no sight check
//take damage -- [Done] - use loop in main game to get around refences
//sprites
//-enemy
//-weapons
//-powerups
//-hud -- [Progress] - health bar and text
//-menu -- [Progress] - uses one image with 3 buttin sprites
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
//Menu class -- [Progress] - can create custom menus
//load level -- [Progress] - need to figure out textures
//Level editor -- [Progress] - need to create new and choose tile and save

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
//reseting the player pos doesnt update the camera -- [Fixed] - the camera now updates to the edges if your at the edge
//reseting the level doesnt reset the players health -- [Fixed] - just set it in the set pos function N.B. dont use setpos except for levels

int main( int argc, char* args[] )
{
	//get base path
	char basePath[255] = "";
	_fullpath(basePath, NULL, sizeof(basePath));
	bpath = basePath;
	cout<<bpath<<endl;

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
		state = Splash;// LevelEdit;

		//<game loop>
		while(!quit)
		{			
			//get framrate
			if(SDL_GetTicks() - start > 1000)
			{
				//printf("fps: %d\n", counted);
				counted = 0;
				start = SDL_GetTicks();
			}
			//get deltatime
			DeltaTime = (SDL_GetTicks() - PrevTicks)/slowTime;
			PrevTicks = SDL_GetTicks();
			SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( renderer );
			SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0x00 );
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
	delete PauseMenu;
	delete EditMenu;
	//delete map
	delete map1;
	//delete player
	delete player;
	delete weapon;
	//level editor
	delete Tinput;
	//delete textures
	SDL_DestroyTexture(tile1);
	SDL_DestroyTexture(tile2);
	SDL_DestroyTexture(tile3);
	SDL_DestroyTexture(tile4);
	SDL_DestroyTexture(tile5);
	SDL_DestroyTexture(tile6);
	SDL_DestroyTexture(tile7);
	delete menurect;
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
	delete []posx; delete []posy; delete []velx; delete []vely;
	init.DeleteTextures(TextureVect);
	init.Exit(window,screenSurface);
	return 0;
}

void Initialise()
{
	//load the tile textures
	tile1 = loader.loadTexturePNG("tiles/footile.png");
	tile2 = loader.loadTexturePNG("tiles/dirtgrass.png");
	tile3 = loader.loadTexturePNG("tiles/glasstile.png");
	tile4 = loader.loadTexturePNG("tiles/Spikes.png");
	tile5 = loader.loadTexturePNG("sprites/sad_onion.png");
	tile6 = loader.loadTexturePNG("sprites/Mine.png");
	tile7 = loader.loadTexturePNG("Sprites/turret_base.png");

	tile = Empty_T;

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

	enemyBullet = loader.loadTexturePNG("sprites/bullet.png");

	for(int i = 0; i<enemybull;i++)
	{
		*(posx+i) = -1;
	}
	//set up the menu
	Main = new MenuContain();
	PauseMenu = new MenuContain();
	EditMenu = new MenuContain();
	int w,h;
	SDL_Texture* newgame = loader.loadTexturePNG("sprites/menu/buttons/NewGame_btn.png");
	SDL_Texture* Exit = loader.loadTexturePNG("sprites/menu/buttons/Exit_btn.png");
	SDL_Texture* LevelEdit = loader.loadTexturePNG("sprites/menu/buttons/LevelEditor_btn.png");
	SDL_Texture* Resume = loader.loadTexturePNG("sprites/menu/buttons/Resume_btn.png");
	SDL_QueryTexture(newgame,NULL,NULL,&w,&h);
	w /=3;
	Main->addButton(newgame,(SCREEN_WIDTH-w)/(3*scalex),70,w,h,"newgame");
	Main->addButton(LevelEdit,(SCREEN_WIDTH-w)/(3*scalex),150,w,h,"Leveledit");
	Main->addButton(Exit,(SCREEN_WIDTH-w)/(3*scalex),230,w,h,"Exit");

	PauseMenu->addButton(Exit,(SCREEN_WIDTH-w)/(2*scalex),200,w,h,"Exit");
	PauseMenu->addButton(Resume,(SCREEN_WIDTH-w)/(2*scalex),100,w,h,"Resume");

	SDL_Texture* loadbut = loader.loadTexturePNG("sprites/menu/buttons/load_btn.png");
	SDL_QueryTexture(loadbut,NULL,NULL,&w,&h);
	w /=3;

	EditMenu->addButton(loadbut,(SCREEN_WIDTH+200)/(2*scalex),100,w,h,"load");

	//set up the menu pretty stuff
	Background = loader.loadTexturePNG("sprites/menu/sofa_720.png");
	Foreground = loader.loadTexturePNG("sprites/menu/camera.png");
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
	//level editor
	Tinput = new TextInput(100,100,300);
	menurect = new DrawRect( 0, 0, 40, SCREEN_WIDTH);

}

bool checkadd(string name)
{
	name = bpath+'\\'+name;
	cout<<name<<endl;
	ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	} else {
		f.close();
		return false;
	}   
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
		if(Main->isPressed("newgame"))
		{
			state = Game;
		}
		if(Main->isPressed("Exit"))
		{
			quit = true;
		}
		if(Main->isPressed("Leveledit"))
		{
			state = LevelEdit;
		}

		if(state == Game)
		{
			loadLevel("maps/map1.txt");
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
		UpdateEnemyBull();
		//check if we should pause
		if(Escprev == true&&Esc == false)
		{
			state = Pause;

		}
		Escprev = Esc;
	}
	if(state == Pause)
	{
		if(PauseMenu->isPressed("Exit"))
		{
			state = MainMenu;
		}
		if(PauseMenu->isPressed("Resume"))
		{
			state = Game;
		}
		//check if the escape key has been pressed
		if(Escprev == true&&Esc == false)
		{
			state = Game;

		}
		Escprev = Esc;
	}
	if(state == LevelEdit)
	{
		SDL_StartTextInput();
		Tinput->Update();
		if(EditMenu->isPressed("load"))
		{
			if(checkadd(Tinput->text))
			{
				loadLevelEditor(bpath+'\\'+Tinput->text);
				cout<<"success"<<endl;
				state = LevelEditPlay;
			}
		}

	}
	else
	{
		SDL_StopTextInput();
	}
	if(state == LevelEditPlay)
	{
		float speed = 10;
		camera.Update(leveleditx,leveledity,map1->getRows(),map1->getCols(),true);
		if(Up)
		{
			leveledity -= speed;

		}
		if(Down)
		{
			leveledity += speed;

		}
		if(Left)
		{
			leveleditx -= speed;

		}
		if(Right)
		{
			leveleditx += speed;

		}
		if(leveledity<(SCREEN_HEIGHT/2) - 80)
		{
			leveledity = (SCREEN_HEIGHT/2) - 80;
		}
		if(leveleditx<(SCREEN_WIDTH/2) - 40)
		{
			leveleditx = (SCREEN_WIDTH/2) - 40;
		}

		if(leveledity> map1->getCols()*40 - (SCREEN_HEIGHT/2)+40)
		{
			leveledity = map1->getCols()*40 -(SCREEN_HEIGHT/2) + 40;
		}
		if(leveleditx>map1->getRows()*40 -(SCREEN_WIDTH/2)+40)
		{
			leveleditx = map1->getRows()*40- (SCREEN_WIDTH/2)+40 ;
		}
		if(MouseState == SDL_BUTTON(1))
		{
			if(mouseY > 40)
			{
				int resy = ((mouseY/scaley)+camera.y)/40;
				int resx = (((mouseX)/scalex)+camera.x)/40;
				if(tile == 0)
				{
					if((resy != 0 && resy != map1->getRows()) ^ (resx != 0 && resx != map1->getCols()))
					{
						map1->setValue(resy,resx,tile);
					}
				}
				else
				{
					map1->setValue(resy,resx,tile);
				}
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
		SDL_RenderCopy(renderer, Background,NULL,&BackRect);
		SDL_RenderCopy(renderer, Foreground,NULL,&ForeRect);
		SDL_RenderCopy(renderer, TextTest,NULL,&TextRect);
		Main->Draw();
	}
	if(state == Game || state == Pause)
	{		
		player->Draw();
		weapon->Draw();
		DrawEnemyBull();
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
	if(state == Pause)
	{
		PauseMenu->Draw();
	}
	if(state == LevelEdit)
	{
		Tinput->Draw();
		EditMenu->Draw();
	}
	if(state == LevelEditPlay)
	{
		map1->Draw();
		menurect->Draw();
	}
}
void UpdateEnemyBull()
{
	for(int i = 0; i<enemybull;i++)
	{
		if(*(posx +i)!=-1)
		{
			if(*(posx+i) != -1)
			{
				*(posx+i)+=*(velx+i)*DeltaTime;
				*(posy+i)+=*(vely+i)*DeltaTime;
			}
			if(*(posx+i) <0 ||*(posx+i)> map1->getCols() *40)
			{
				*(posx+i) = -1;
			}
			if(map1->GetValue(*(posx+i)/40,*(posy+i)/40) == 1 || map1->GetValue(*(posx+i)/40,(*(posy+i)+10)/40) == 1)
			{
				*(posx+i) = -1;
			}
			SDL_Rect bulBox;
			bulBox.x = *(posx+i);
			bulBox.y = *(posy+i);
			bulBox.w = 10;
			bulBox.h = 10;
			player->hittest(bulBox,5);			
		}
	}
}
void DrawEnemyBull()
{
	SDL_Rect bulRect;
	bulRect.w = 10;
	bulRect.h = 10;
	for(int i = 0; i<enemybull;i++)
	{
		if(*(posx+i) != -1)
		{
			bulRect.x = *(posx + i) - camera.x;
			bulRect.y = *(posy + i) - camera.y;
			SDL_RenderCopy(renderer, texture,NULL,&bulRect);
		}
	}
}
void loadLevel(string mapadd)
{
	//no leak but may want to do SDL_DESTROY_TEXTURES
	tiles.clear();
	for(vector<Enemy*>::iterator it = Enemies.begin(); it != Enemies.end(); ++it)
	{
		delete *it;
	}
	for(vector<Blast*>::iterator it = Blasts.begin(); it != Blasts.end();++it)
	{
		delete *it;
	}
	Blasts.clear();
	Enemies.clear();

	tiles.push_back(tile1);
	tiles.push_back(tile2);
	tiles.push_back(tile3);
	tiles.push_back(tile4);
	delete map1;
	map1= loader.initMap(map1,mapadd,tiles);
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
	player->setpos(playerStartX,playerStartY);
}

void loadLevelEditor(string mapadd)
{
	//no leak but may want to do SDL_DESTROY_TEXTURES
	tiles.clear();
	for(vector<Enemy*>::iterator it = Enemies.begin(); it != Enemies.end(); ++it)
	{
		delete *it;
	}
	for(vector<Blast*>::iterator it = Blasts.begin(); it != Blasts.end();++it)
	{
		delete *it;
	}
	Blasts.clear();
	Enemies.clear();

	tiles.push_back(tile1);
	tiles.push_back(tile2);
	tiles.push_back(tile3);
	tiles.push_back(tile4);
	tiles.push_back(tile5);
	tiles.push_back(tile6);
	tiles.push_back(tile7);
	delete map1;
	map1= loader.initMap(map1,mapadd,tiles);
}