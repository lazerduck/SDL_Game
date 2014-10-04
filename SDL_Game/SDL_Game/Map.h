#pragma once

class Map
{
private:
	int rows;
	int columns;
	int size;

	int* data;

	vector<SDL_Texture*> Tiles;
	SDL_Rect DrawRect;
public:

	Map(void)
	{
		rows = 0;
		columns = 0;
		size = 0;
		data = NULL;

		DrawRect.x = 0;
		DrawRect.y = 0;
		DrawRect.w = 40;
		DrawRect.h = 40;	
	}

	Map(int row, int column)
	{
		rows = row;
		columns = column;
		size = row*column;
		data = new int[size];

		DrawRect.x = 0;
		DrawRect.y = 0;
		DrawRect.w = 40;
		DrawRect.h = 40;
	}
	Map(int row, int column, int* Data)
	{
		rows = row;
		columns = column;
		size = row*column;

		data = new int[size];
		for(int i = 0; i<size;i++)
		{
			data[i] = Data[i];
		}

		DrawRect.x = 0;
		DrawRect.y = 0;
		DrawRect.w = 40;
		DrawRect.h = 40;
	}
	Map(int row, int column, int* Data, vector<SDL_Texture*> textures)
	{
		rows = row;
		columns = column;
		size = row*column;
		Tiles = textures;

		data = new int[size];
		for(int i = 0; i<size;i++)
		{
			data[i] = Data[i];
		}

		DrawRect.x = 0;
		DrawRect.y = 0;
		DrawRect.w = 40;
		DrawRect.h = 40;

	}

	void SetData(int* Data)
	{
		delete data;
		data = new int[size];
		for(int i = 0; i<size;i++)
		{
			data[i] = Data[i];
		}
	}

	int* GetData()
	{
		int* ret = new int[size];
		for(int i = 0; i<size; i++)
		{
			ret[i] = data[i];
		}
	}

	void SetTexures(vector<SDL_Texture*> textures)
	{
		for(vector<SDL_Texture*>::iterator it = textures.begin(); it != textures.end();++it)
		{
			Tiles.push_back(*it);
		}
	}

	int GetValue(int x, int y)
	{
		if(x<0 || y<0 ||x>columns||y>rows)
		{
			return-1;
		}
		return data[x+(columns*y)];
	}

	void Draw()
	{
		for(int i = 0;i<rows;i++)
		{
			for(int j = 0; j<columns;j++)
			{
				DrawRect.x = (j*40);
				DrawRect.y = (i*40);
				if( DrawRect.x<camera.view.x+camera.view.w && camera.view.y < DrawRect.y+DrawRect.h && camera.view.x < DrawRect.x+DrawRect.w && DrawRect.y < camera.view.y+camera.view.h)
				{
					int texnum = data[j+(columns*i)]-1;
					if(texnum < Tiles.size() && texnum>=0)
					{
						DrawRect.x = (j*40) - camera.x;
						DrawRect.y = (i*40) - camera.y;
						SDL_RenderCopy(renderer,Tiles[texnum],NULL,&DrawRect);
					}
				}
			}
		}
	}
	int getRows()
	{
		return rows;
	}
	int getCols()
	{
		return columns;
	}
	void setValue(int i, int j,int val)
	{
		if(i < 0 || j < 0||i>rows || j > columns)
		{
			return;
		}
		data[j+(columns*i)] = val;
	}

	~Map(void)
	{
		for(vector<SDL_Texture*>::iterator it = Tiles.begin();it!=Tiles.end();++it)
		{
			SDL_DestroyTexture(*it);
		}
		delete data;
	}
};

