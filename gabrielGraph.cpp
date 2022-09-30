#include "gabrielGraph.h"
#include "dungeonGenerator.h"
#include "Rooms.h"

GabrielGraph::GabrielGraph()
{
}

GabrielGraph::~GabrielGraph()
{
	BaseGraphGenerator::~BaseGraphGenerator();
}

void GabrielGraph::Run()
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

void GabrielGraph::PreStep() 
{
	primary = 0;
	finishedStep = false;
	rooms = generator->roomGenerator;
}

void GabrielGraph::Step() 
{
	for (unsigned int j = primary + 1; j < rooms->rooms.size(); j++)
	{
		// Find the circle center
		float dx = (rooms->rooms[primary]->centerX + rooms->rooms[j]->centerX) / 2.f;
		float dy = (rooms->rooms[primary]->centerY + rooms->rooms[j]->centerY) / 2.f;
		float radius = Distance2D(rooms->rooms[primary]->centerX, rooms->rooms[primary]->centerY, rooms->rooms[j]->centerX, rooms->rooms[j]->centerY) / 2.f;

		// Check the circle against all other points
		bool isWithinCircle = false;
		for (unsigned int m = 0; m < rooms->rooms.size(); m++)
		{
			// Skip the ones we are testing against
			if (m == primary || m == j)
			{
				continue;
			}

			// Check the radius
			float tradius = Distance2D(rooms->rooms[m]->centerX, rooms->rooms[m]->centerY, (int)dx, (int)dy);
			if (tradius <= radius)
			{
				isWithinCircle = true;
				break;
			}
		}

		// Did we find anything?
		if (isWithinCircle == false)
		{
			AddEdge(rooms->rooms[primary], rooms->rooms[j]); // Check first pair
		}
	}

	// Increment primary and carry on
	if (primary < rooms->rooms.size() - 1)
	{
		primary++;
	}
	else
	{
		finishedStep = true;
	}
}

void GabrielGraph::PostStep()
{

}