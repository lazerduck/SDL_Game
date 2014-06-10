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
		return data[x+(columns*y)];
	}

	void Draw()
	{
		for(int i = 0;i<rows;i++)
		{
			for(int j = 0; j<columns;j++)
			{
				int texnum = data[j+(columns*i)]-1;
				if(texnum < Tiles.size() && texnum>=0)
				{
					DrawRect.x = j*40+playerX;
					DrawRect.y = i*40+playerY;
					SDL_RenderCopy(renderer,Tiles[texnum],NULL,&DrawRect);
				}
			}
		}
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

