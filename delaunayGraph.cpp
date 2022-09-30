#include "delaunayGraph.h"
#include "dungeonGenerator.h"
#include "Rooms.h"

DelaunayGraph::DelaunayGraph()
{
}

DelaunayGraph::~DelaunayGraph()
{
	BaseGraphGenerator::~BaseGraphGenerator();
}

void DelaunayGraph::Run()
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

void DelaunayGraph::PreStep() 
{
	primary = 0;
	secondary = primary + 1;
	finishedStep = false;
	rooms = generator->roomGenerator;
}

void DelaunayGraph::Step()
{
	for (unsigned int k = secondary + 1; k < rooms->rooms.size(); k++)
	{
		// Find center of the circle formed by the three points
		float yaDelta = rooms->rooms[secondary]->centerY - rooms->rooms[primary]->centerY;
		float xaDelta = rooms->rooms[secondary]->centerX - rooms->rooms[primary]->centerX;
		float ybDelta = rooms->rooms[k]->centerY - rooms->rooms[secondary]->centerY;
		float xbDelta = rooms->rooms[k]->centerX - rooms->rooms[secondary]->centerX;
		float centerX, centerY;

		float aSlope = yaDelta / xaDelta;
		float bSlope = ybDelta / xbDelta;

		// Find center between the two of the three points
		float AB_midx = (rooms->rooms[primary]->centerX + rooms->rooms[secondary]->centerX) / 2;
		float AB_midy = (rooms->rooms[primary]->centerY + rooms->rooms[secondary]->centerY) / 2;
		float BC_midx = (rooms->rooms[secondary]->centerX + rooms->rooms[k]->centerX) / 2;
		float BC_midy = (rooms->rooms[secondary]->centerY + rooms->rooms[k]->centerY) / 2;

		if (yaDelta == 0) // Uh oh, a delta is infinite, compensate for it
		{
			centerX = AB_midx;
			if (xbDelta == 0)
			{
				centerY = BC_midy;
			}
			else
			{
				centerY = BC_midy + (BC_midx - centerX) / bSlope;
			}
		}
		else if (ybDelta == 0) // Uh oh, a delta is infinite, compensate for it
		{
			centerX = BC_midx;
			if (xbDelta == 0)
			{
				centerY = AB_midy;
			}
			else
			{
				centerY = AB_midy + (AB_midx - centerX) / aSlope;
			}
		}
		else if (xaDelta == 0) // Uh oh, a delta is infinite, compensate for it
		{
			centerY = AB_midy;
			centerX = bSlope * (BC_midy - centerY) + BC_midx;
		}
		else if (xbDelta == 0) // Uh oh, a delta is infinite, compensate for it
		{
			centerY = BC_midy;
			centerX = aSlope * (AB_midy - centerY) + AB_midx;
		}
		else
		{
			centerX = (aSlope * bSlope * (AB_midy - BC_midy) - aSlope * BC_midx + bSlope * AB_midx) / (bSlope - aSlope);
			centerY = AB_midy - (centerX -AB_midx) / aSlope;
		}

		// Find radius
		float radius = Distance2D(rooms->rooms[primary]->centerX, rooms->rooms[primary]->centerY, (int)centerX, (int)centerY);

		// Check against all triangles if any of them fall within the circle
		bool isWithinCircle = false;
		for (unsigned int m = 0; m < rooms->rooms.size(); m++)
		{
			// Skip the ones we are testing against
			if (m == primary || m == secondary || m == k)
			{
				continue;
			}

			// Check the radius
			float tradius = Distance2D(rooms->rooms[m]->centerX, rooms->rooms[m]->centerY, (int)centerX, (int)centerY);
			if (tradius <= radius)
			{
				isWithinCircle = true;
				break;
			}
		}

		// Did we find anything?
		if (isWithinCircle == false)
		{
			AddEdge(rooms->rooms[primary], rooms->rooms[secondary]); // Check first pair
			AddEdge(rooms->rooms[primary], rooms->rooms[k]); // Second pair
			AddEdge(rooms->rooms[secondary], rooms->rooms[k]); // Third pair
		}
	}

	// Increment secondary and carry on
	if (secondary < rooms->rooms.size() - 1)
	{
		secondary++;
	}
	else
	{
		primary++;
		secondary = primary + 1;
	}

	// Check if done
	if (primary >= rooms->rooms.size() - 2)
	{
		finishedStep = true;
	}
}

void DelaunayGraph::PostStep()
{
	// Make sure all rooms have at least a neighbor, otherwise fix it!
	for (unsigned int m = 0; m < rooms->rooms.size(); m++)
	{
		// No neighbors, connect to the two closest nodes and hope they don't intersect
		if (rooms->rooms[m]->node->neighbors.size() == 0)
		{
			float firstClose = FLT_MAX, secondClose = FLT_MAX;
			int firstId, secondId;

			for (unsigned int n = 0; n < rooms->rooms.size(); n++)
			{
				// Skip self
				if (m == n)
				{
					continue;
				}

				// Find distance
				float dist = Distance2D(rooms->rooms[m]->centerX, rooms->rooms[m]->centerY, rooms->rooms[n]->centerX, rooms->rooms[n]->centerY);

				// If it isn't the closest, could it be second closest?
				if (dist <= firstClose)
				{
					firstClose = dist;
					firstId = n;
				}
				else if (dist <= secondClose)
				{
					secondClose = dist;
					secondId = n;
				}
			}

			// Add the neighbors
			AddEdge(rooms->rooms[m], rooms->rooms[firstId]); // Check first pair
			AddEdge(rooms->rooms[m], rooms->rooms[secondId]); // Check second pair
		}
	}
}