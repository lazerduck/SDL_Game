#pragma once
class Mine :
	public Enemy
{
private:
	bool explode;
	gTimer boom;
	SDL_Texture *Boom;
public:

	Mine(void)
	{
	}

	Mine(SDL_Texture* tex,SDL_Texture *boom, int X, int Y)
	{
		Boom= boom;
		X = X*40;
		Y = Y*40;
		dst.x = X;
		dst.y = Y;
		dst.w = 40;
		dst.h = 40;
		x = X;
		y = Y;
		vely = 0;
		velx = 0;
		health = 2;
		texture = tex;
		damage = 50;
		hitcheck = false;
	}

	void Update(Player* player,Map *map)
	{
		hitcheck = false;
		if(hit(player->getRect(),0))
		{
			health = 0;
		}
		for(vector<Blast*>::iterator it = Blasts.begin(); it != Blasts.end();++it)
		{
			if(std::pow((*it)->getX()-(x+20),2) + std::pow((y+20)-(*it)->getY(),2) <= (std::pow((*it)->getR()+20,2)))
			{
				health = 0;
			}
		}
		dst.x =(int) x -camera.x;
		dst.y = (int)y - camera.y;
	}

	~Mine(void)
	{
		Blast *b = new Blast(Boom,x+(dst.w/2),y+(dst.h/2));
		Blasts.push_back(b);

	}
};

