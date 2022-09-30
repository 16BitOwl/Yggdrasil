#include "Grid.h"
#include "dungeonGenerator.h"

Grid::Grid()
{
	x = y = 0;
	width = height = 0;
	grid = NULL;
	hasCells = false;
}

Grid::Grid(int _x, int _y, unsigned int _width, unsigned int _height, int _padding)
{
	grid = NULL;

	Offset(_x, _y);
	Setup(_width, _height);
}

Grid::~Grid()
{
	Clear();
}

void Grid::LoadData()
{
	CSimpleIniA iniReader;

	// Load settings file
	iniReader.SetUnicode();
	iniReader.LoadFile("dungeon.ini");
}

void Grid::Setup(unsigned int _width, unsigned int _height)
{
	// Store values
	hasCells = true;
	width = _width;
	height = _height;

	// Create dungeon grid
	grid = new GridCell*[width];
	for (unsigned int i = 0; i < width; i++)
	{
		grid[i] = new GridCell[height];
	}
}

void Grid::Offset(int _x, int _y)
{
	x = _x;
	y = _y;
}

bool Grid::ValidPosition(int _x, int _y)
{
	if (_x < 0 || _x >= width)
	{
		return false;
	}
	if (_y < 0 || _y >= height)
	{
		return false;
	}

	return true;
}

void Grid::Clear()
{
	// Clear grid
	if (hasCells)
	{
		for (unsigned int i = 0; i < width; i++)
		{
			delete[] grid[i];
		}
		delete[] grid;
	}

	gridRectStorage.clear();
	width = 0;
	height = 0;
}

void Grid::Run() 
{
	// Run pre step setup
	PreStep();

	// Loop step until finished
	while (finishedStep == false)
	{
		Step();
	}

	// Run post step checks
	PostStep();
}

void Grid::PreStep()
{
	finishedStep = false;

	// Create a new grid
	Setup(generator->width, generator->height);

	// Load grid data from rects
	for (unsigned int i = 0; i < generator->roomGenerator->rooms.size(); i++)
	{
		FromGridData(generator->roomGenerator->rooms[i]->grid, generator->roomGenerator->rooms[i]->x1, generator->roomGenerator->rooms[i]->y1, generator->roomGenerator->rooms[i]->width, generator->roomGenerator->rooms[i]->height);
	}
	for (unsigned int i = 0; i < generator->corridorGenerator->corridors.size(); i++)
	{
		for (unsigned int j = 0; j < generator->corridorGenerator->corridors[i]->blocks.size(); j++)
		{
			FromGridRect(generator->corridorGenerator->corridors[i]->blocks[j], CORRIDOR);
		}
	}
}

void Grid::Step()
{
	for (unsigned int i = 0; i < gridRectStorage.size(); i++)
	{
		for (unsigned int m = 0; m < gridRectStorage[i]->rect->width; m++)
		{
			for (unsigned int n = 0; n < gridRectStorage[i]->rect->height; n++)
			{
				unsigned int tx = gridRectStorage[i]->rect->x1 + m;
				unsigned int ty = gridRectStorage[i]->rect->y1 + n;

				// Make sure where are not out of bounds
				if (ValidPosition(tx, ty))
				{
					// Replace only if type has larger priority
					if (grid[tx][ty].type < gridRectStorage[i]->type)
					{
						grid[tx][ty].type = gridRectStorage[i]->type;
					}
				}
			}
		}
	}

	finishedStep = true;
}

void Grid::PostStep()
{

}

void Grid::FromGridRect(GridRect* _gridRect, CellType _rectType)
{
	gridRectStorage.push_back(new GridRectInfo(_gridRect, _rectType));
}

void Grid::FromGridData(GridCell** _grid, int _x, int _y, int _width, int _height)
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			// Make sure where are not out of bounds
			if (ValidPosition(i + _x, j + _y))
			{
				grid[i + _x][j + _y] = _grid[i][j];
			}
		}
	}
}