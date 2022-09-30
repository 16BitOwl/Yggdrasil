#include "Walls.h"
#include "dungeonGenerator.h"

WallGen::WallGen()
{
}

WallGen::~WallGen()
{
}

void WallGen::Clear() 
{
	walls.clear();
}

void WallGen::Run()
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

void WallGen::PreStep() 
{
	grid = generator->dungeonGrid;
	primary = 0;
	finishedStep = false;
}

void WallGen::Step()
{
	for (unsigned int n = 0; n < grid->height; n++)
	{
		int x = primary;
		int y = n;

		// We must stand on a none-empty grid to continue
		if (grid->ValidPosition(x, y))
		{
			if (grid->grid[x][y].type == EMPTY)
			{
				continue;
			}
		}

		// Check North
		bool wallNorth = true;
		if (grid->ValidPosition(x, y - 1))
		{
			if (grid->grid[x][y - 1].type != EMPTY)
			{
				wallNorth = false;
			}
		}
		if (wallNorth)
		{
			WallData* temp = new WallData();
			temp->x1 = x;
			temp->y1 = y;
			temp->x2 = x + 1;
			temp->y2 = y;
			walls.push_back(temp);
		}

		// Check South
		bool wallSouth = true;
		if (grid->ValidPosition(x, y + 1))
		{
			if (grid->grid[x][y + 1].type != EMPTY)
			{
				wallSouth = false;
			}
		}
		if (wallSouth)
		{
			WallData* temp = new WallData();
			temp->x1 = x;
			temp->y1 = y + 1;
			temp->x2 = x + 1;
			temp->y2 = y + 1;
			walls.push_back(temp);
		}

		// Check West
		bool wallWest = true;
		if (grid->ValidPosition(x - 1, y))
		{
			if (grid->grid[x - 1][y].type != EMPTY)
			{
				wallWest = false;
			}
		}
		if (wallWest)
		{
			WallData* temp = new WallData();
			temp->x1 = x;
			temp->y1 = y;
			temp->x2 = x;
			temp->y2 = y + 1;
			walls.push_back(temp);
		}

		// Check East
		bool wallEast = true;
		if (grid->ValidPosition(x + 1, y))
		{
			if (grid->grid[x + 1][y].type != EMPTY)
			{
				wallEast = false;
			}
		}
		if (wallEast)
		{
			WallData* temp = new WallData();
			temp->x1 = x + 1;
			temp->y1 = y;
			temp->x2 = x + 1;
			temp->y2 = y + 1;
			walls.push_back(temp);
		}
	}

	// Increment primary and carry on
	if (primary < grid->width - 1)
	{
		primary++;
	}
	else
	{
		finishedStep = true;
	}
}

void WallGen::PostStep()
{

}