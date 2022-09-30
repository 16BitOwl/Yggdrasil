#include "corridors.h"
#include "dungeonGenerator.h"

CorridorGen::CorridorGen()
{
	corridorWidth = 1;
	width = height = 0;
}

CorridorGen::~CorridorGen()
{

}

void CorridorGen::Clear()
{
	for (unsigned int i = 0; i < corridors.size(); i++)
	{
		corridors[i]->blocks.clear();
	}
	corridors.clear();
	width = height = 0;
}

void CorridorGen::LoadData() 
{
	CSimpleIniA iniReader;

	// Load settings file
	iniReader.SetUnicode();
	iniReader.LoadFile("dungeon.ini");

	corridorWidth = (int)iniReader.GetDoubleValue("Corridors", "Width", 1); // Corridor width
	ratioAlgorithms = (int)iniReader.GetDoubleValue("Corridors", "AlgorithmRatio", 30); // Corridor algorithm ratio
}

void CorridorGen::Run()
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

void CorridorGen::PreStep()
{
	graph = generator->graphSimplified;
	finishedStep = false;
	primary = 0;
}

void CorridorGen::Step() 
{
	for (unsigned int j = 0; j < graph->nodes[primary]->neighbors.size(); j++)
	{
		// Make sure the corridor has not been spawned yet
		bool corridorExists = false;
		for (unsigned int k = 0; k < corridors.size(); k++)
		{
			if ((corridors[k]->leftRoom == graph->nodes[primary] && corridors[k]->rightRoom == graph->nodes[primary]->neighbors[j]->node) ||
				(corridors[k]->leftRoom == graph->nodes[primary] && corridors[k]->rightRoom == graph->nodes[primary]->neighbors[j]->node))
			{
				corridorExists = true;
				break;
			}
		}

		// No corridor, generate!
		if (corridorExists == false)
		{
			// ====== L-shapes ======
			Corridor* corridor = new Corridor();
			corridor->leftRoom = graph->nodes[primary];
			corridor->rightRoom = graph->nodes[primary]->neighbors[j]->node;

			// Find optimal portal between the rooms
			Portal* portal1,* portal2;
			float dist = FLT_MAX, tDist;
			for (unsigned int u = 0; u < corridor->leftRoom->room->portals.size(); u++)
			{
				for (unsigned int y = 0; y < corridor->rightRoom->room->portals.size(); y++)
				{
					tDist = Distance2D((float)corridor->leftRoom->room->portals[u]->x, (float)corridor->leftRoom->room->portals[u]->y, (float)corridor->rightRoom->room->portals[y]->x, (float)corridor->rightRoom->room->portals[y]->y);
					if (tDist < dist)
					{
						portal1 = corridor->leftRoom->room->portals[u];
						portal2 = corridor->rightRoom->room->portals[y];
						dist = tDist;
					}
				}
			}

			// Determine which algorithm to use this time
			int randAlgorithm = RandomInterval(0, 100);
			if (randAlgorithm >= ratioAlgorithms)
			{
				// Calculate L-shape corridor
				int w = portal1->x - portal2->x;
				int h = portal1->y - portal2->y;

				if (w < 0)
				{
					if (h < 0)
					{
						// Line 1
						corridor->line1x1 = portal1->x;
						corridor->line1y1 = portal2->y;
						corridor->line1x2 = portal1->x + abs(w);
						corridor->line1y2 = portal2->y;
						GenerateCorridorBlocksHorizontal(portal1->x, portal2->y, abs(w), *corridor);

						// Line 2
						corridor->line2x1 = portal1->x;
						corridor->line2y1 = portal1->y;
						corridor->line2x2 = portal1->x;
						corridor->line2y2 = portal1->y + abs(h);
						GenerateCorridorBlocksVertical(portal1->x, portal1->y, abs(h), *corridor);
					}
					else if (h > 0)
					{
						// Line 1
						corridor->line1x1 = portal1->x;
						corridor->line1y1 = portal2->y;
						corridor->line1x2 = portal1->x + abs(w);
						corridor->line1y2 = portal2->y;
						GenerateCorridorBlocksHorizontal(portal1->x, portal2->y, abs(w), *corridor);

						// Line 2
						corridor->line2x1 = portal1->x;
						corridor->line2y1 = portal2->y;
						corridor->line2x2 = portal1->x;
						corridor->line2y2 = portal2->y + abs(h);
						GenerateCorridorBlocksVertical(portal1->x, portal2->y, abs(h), *corridor);
					}
					else
					{
						// Line 1
						corridor->line1x1 = portal1->x;
						corridor->line1y1 = portal1->y;
						corridor->line1x2 = portal1->x + abs(w);
						corridor->line1y2 = portal1->y;
						GenerateCorridorBlocksHorizontal(portal1->x, portal1->y, abs(w), *corridor);
					}
				}
				else if (w > 0)
				{
					if (h < 0)
					{
						// Line 1
						corridor->line1x1 = portal2->x;
						corridor->line1y1 = portal1->y;
						corridor->line1x2 = portal2->x + abs(w);
						corridor->line1y2 = portal1->y;
						GenerateCorridorBlocksHorizontal(portal2->x, portal1->y, abs(w), *corridor);

						// Line 2
						corridor->line2x1 = portal2->x;
						corridor->line2y1 = portal1->y;
						corridor->line2x2 = portal2->x;
						corridor->line2y2 = portal1->y + abs(h);
						GenerateCorridorBlocksVertical(portal2->x, portal1->y, abs(h), *corridor);
					}
					else if (h > 0)
					{
						// Line 1
						corridor->line1x1 = portal2->x;
						corridor->line1y1 = portal2->y;
						corridor->line1x2 = portal2->x + abs(w);
						corridor->line1y2 = portal2->y;
						GenerateCorridorBlocksHorizontal(portal2->x, portal2->y, abs(w), *corridor);

						// Line 2
						corridor->line2x1 = portal1->x;
						corridor->line2y1 = portal2->y;
						corridor->line2x2 = portal1->x;
						corridor->line2y2 = portal2->y + abs(h);
						GenerateCorridorBlocksVertical(portal1->x, portal2->y, abs(h), *corridor);
					}
					else
					{
						// Line 1
						corridor->line1x1 = portal2->x;
						corridor->line1y1 = portal2->y;
						corridor->line1x2 = portal2->x + abs(w);
						corridor->line1y2 = portal2->y;
						GenerateCorridorBlocksHorizontal(portal2->x, portal2->y, abs(w), *corridor);
					}
				}
				else
				{
					if (h < 0)
					{
						// Line 1
						corridor->line1x1 = portal1->x;
						corridor->line1y1 = portal1->y;
						corridor->line1x2 = portal1->x;
						corridor->line1y2 = portal1->y + abs(h);
						GenerateCorridorBlocksVertical(portal1->x, portal1->y, abs(h), *corridor);
					}
					else if (h > 0)
					{
						// Line 1
						corridor->line1x1 = portal2->x;
						corridor->line1y1 = portal2->y;
						corridor->line1x2 = portal2->x;
						corridor->line1y2 = portal2->y + abs(h);
						GenerateCorridorBlocksVertical(portal2->x, portal2->y, abs(h), *corridor);
					}
				}
			}
			else
			{
				// ====== Bresenham's Line algorithm ======
				int x1 = portal1->x, x2 = portal2->x, y1 = portal1->y, y2 = portal2->y;
				bool steep = abs(portal2->y - portal1->y) > abs(portal2->x - portal1->x);
				if (steep) 
				{
					swap(x1, y1);
					swap(x2, y2);
				}
				if (x1 > x2)
				{
					swap(x1, x2);
					swap(y1, y2);
				}
				int dx = (x2 - x1);
				int dy = abs(y2 - y1);
				int err = (dx / 2);
				int yStep = (y1 < y2 ? 1 : -1);
				int y = y1;
				int oldY = y;

				for (int x = x1; x <= x2; ++x)
				{
					// Plot y > x
					if (steep)
					{
						Plot(y, x, *corridor);
						if (oldY != y && corridorWidth == 1)
						{
							Plot(y, x - 1, *corridor);
						}
					}

					// Plot x > y
					if (!steep)
					{
						Plot(x, y, *corridor);
						if (oldY != y && corridorWidth == 1)
						{
							Plot(x - 1, y, *corridor);
						}
					}

					// Update error stores
					err = err - dy;
					if (err < 0)
					{
						y += yStep; 
						err += dx;
					}
				}
			}

			// Add corridor
			corridors.push_back(corridor);
		}
	}

	// Increment primary and carry on
	if (primary < graph->nodes.size() - 1)
	{
		primary++;
	}
	else
	{
		finishedStep = true;
	}
}

void CorridorGen::PostStep() 
{
	GetSize(generator->width, generator->height);
}

void CorridorGen::GenerateCorridorBlocksVertical(int _x, int _y, int _height, Corridor& _corridor)
{
	GridRect* temp = new GridRect(_x, _y, _x + corridorWidth, _y + _height);
	temp->width = corridorWidth;
	temp->height = _height;
	_corridor.blocks.push_back(temp);

	if (width < _x + corridorWidth)
	{
		width = _x + corridorWidth;
	}
	if (height < _y + _height)
	{
		height = _y + _height;
	}
}

void CorridorGen::GenerateCorridorBlocksHorizontal(int _x, int _y, int _width, Corridor& _corridor)
{
	GridRect* temp = new GridRect(_x, _y, _x + _width, _y + corridorWidth);
	temp->width = _width;
	temp->height = corridorWidth;
	_corridor.blocks.push_back(temp);

	if (width < _x + _width)
	{
		width = _x + _width;
	}
	if (height < _y + corridorWidth)
	{
		height = _y + corridorWidth;
	}
}

bool CorridorGen::Plot(int _x, int _y, Corridor& _corridor)
{
	GridRect* temp = new GridRect(_x, _y, _x, _y);
	temp->width = corridorWidth;
	temp->height = corridorWidth;
	_corridor.blocks.push_back(temp);

	if (width < _x + temp->width)
	{
		width = _x + temp->width;
	}
	if (height < _y + temp->height)
	{
		height = _y + temp->height;
	}

	return true;
}

void CorridorGen::GetSize(int& _width, int& _height)
{
	if (_width < width)
	{
		_width = width;
	}
	if (_height < height)
	{
		_height = height;
	}
}