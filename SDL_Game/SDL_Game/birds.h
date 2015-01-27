#pragma once
class birds : public Enemy
{
public:
	struct vec2
	{
	public:
		int x;
		int y;
		vec2(){}
		vec2(int X, int Y)
		{
			x = X;
			y = Y;
		}
		bool operator==(vec2 rhs)
		{
			if(x == rhs.x && y == rhs.y)
			{
				return true;
			}
			return false;
		}
		bool operator!=(vec2 rhs)
		{
			if(x == rhs.x && y == rhs.y)
			{
				return false;
			}
			return true;
		}
	};
	//node sturct
	struct node
	{
	public:
		vec2 pos;
		vec2 prev;
		float gScore;
		float fScore;
	};
	vec2 target;
	//result path
	vector<vec2> path;
	//heuristic
	Map* heuristic;
	//open list
	vector<node> open;
	//closed list
	vector<node> closed;
	//are we moving
	bool motion;
	gTimer hitTimer;
	birds(void)
	{
		
	}

	birds(int X, int Y, SDL_Texture *Texture)
	{
		dst.x = X*40;
		dst.y = Y*40;
		x = dst.x;
		y = dst.y;
		texture = Texture;
		SDL_QueryTexture(texture,NULL,NULL,&dst.w,&dst.h);
		dst.h /= 2; dst.w /= 2;
		motion = false;
		heuristic = NULL;
		health = 10;
		damage = 10;
		rot = 0;
		hitcheck = false;
		flip = SDL_FLIP_NONE;
	}

	void Update(Player* player,Map *map)
	{
		hitTimer.Update(DeltaTime);
		if(hitcheck&&hitTimer.Time == 0)
		{
			hitTimer.Start();
		}
		if(hitTimer.Time > 100)
		{
			hitcheck = false;
			hitTimer.Stop();
		}
		dst.x =(int) x -camera.x;
		dst.y = (int)y - camera.y;
		if(heuristic == NULL)
		{
			heuristic = new Map(map->getRows(),map->getCols());
		}
		if(path.size()>0)
		{
			move();
		}
		if(target.x != player->getX()/40 || target.y != player->getY()/40)
		{
			target.x = player->getX()/40; target.y = player->getY()/40;
			int test = abs(target.x - x/40) + abs(target.y - y/40);
			if(test<10)
			{
			calcHeuristic(target);
			calcPath(player, map);
			}
		}
		
	}
	void checkPos(node current, Map* map)
	{
		if((1<<map->GetValue(current.pos.x, current.pos.y)&group1))
		{
			return;
		}
		else
		{
			for(vector<node>::iterator it = closed.begin(); it!= closed.end(); ++it)
			{
				if(current.pos == (*it).pos)
				{
					return;
				}
			}
			for(vector<node>::iterator it = open.begin(); it!= open.end(); ++it)
			{
				if(current.pos == (*it).pos)
				{
					if(current.gScore < (*it).gScore)
					{
						(*it).gScore = current.gScore;
						(*it).fScore = (*it).gScore + heuristic->GetValue((*it).pos.x,(*it).pos.y);
						(*it).prev = current.prev;
						return;
					}
					return;
				}
			}
			open.push_back(current);
		}
	}
	void calcPath(Player* player, Map *map)
	{
		cout<<"calculating path"<<endl;
		closed.clear();
		open.clear();
		path.clear();
		node start;
		start.pos.x = x/40; start.pos.y =y/40;
		start.prev.x = -1; start.prev.y = -1;
		start.gScore = 0;
		start.fScore = heuristic->GetValue(start.pos.x,start.pos.y);
		open.push_back(start);
		int loopCount = 0;
		//begin loop
		while(open.size()!= 0)
		{
			loopCount++;
			if(loopCount>40)
			{
				break;
			}
			node current;
			float f = 1000000;
			for(auto it = open.begin(); it!= open.end(); ++it)
			{
				if((*it).fScore < f)
				{
					current  = (*it);
					f = (*it).fScore;
				}
			}
			if(current.pos == target)
			{
				createPath(current);
				break;
			}
			for(auto it = open.begin(); it!= open.end(); ++it)
			{
				if((*it).pos == current.pos)
				{
					open.erase(it);
					break;
				}
			}
			closed.push_back(current);
			//search for neighbours
			current.gScore += 1;
			current.prev = current.pos;
			//check possible paths
			current.pos.x +=1;
			current.fScore = current.gScore + heuristic->GetValue(current.pos.x,current.pos.y);
			checkPos(current,map);
			current.pos.x -=2;
			current.fScore = current.gScore + heuristic->GetValue(current.pos.x,current.pos.y);
			checkPos(current,map);
			current.pos.x +=1;
			current.pos.y += 1;
			current.fScore = current.gScore + heuristic->GetValue(current.pos.x,current.pos.y);
			checkPos(current,map);
			current.pos.y -= 2;
			current.fScore = current.gScore + heuristic->GetValue(current.pos.x,current.pos.y);
			checkPos(current,map);
		}
	}

	void createPath(node current)
	{
		while (current.prev != vec2(-1,-1))
		{
			current.pos.x *= 40;
			current.pos.y *= 40;
			path.push_back(current.pos);
			for(vector<node>::iterator it = closed.begin(); it != closed.end(); ++it)
			{
				if((*it).pos == current.prev)
				{
					current = (*it);
					break;
				}
			}
		}
	}
	void calcHeuristic(vec2 goal)
	{
		for(int i = 0; i < heuristic->getRows(); i++)
		{
			for(int j = 0; j < heuristic->getCols(); j++)
			{
				int val = abs(i-goal.y) + abs(j- goal.x);
				heuristic->setValue(i,j,val);
			}
		}
	}
	void move()
	{
		vec2 curr = path.back();
		if(curr.x - x>0)
		{
			x+=0.5;
		}
		if(curr.x - x<0)
		{
			x-=0.5;
		}
		if(curr.y - y>0)
		{
			y+=0.5;
		}
		if(curr.y - y<0)
		{
			y-=0.5;
		}
		if(curr.x == x && curr.y == y)
		{
			path.pop_back();
		}
	}
	void Draw() 
	{
		if(hitcheck)
		{
			SDL_SetTextureAlphaMod( texture, 0x40 );
		}
		SDL_RenderCopy(renderer, texture,NULL,&dst);
		if(hitcheck)
		{
			SDL_SetTextureAlphaMod( texture, 0xff );
		}
		SDL_Rect tect;
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0x0F );
		//for(auto it = path.rbegin(); it != path.rend(); ++it)
		//{
		//	tect.x = ((*it).x) - camera.x;
		//	tect.y = ((*it).y) - camera.y;
		//	tect.w = 10;
		//	tect.h = 10;
		//	SDL_RenderFillRect(renderer,&tect);
		//}
	}
	~birds(void)
	{
	}
};

