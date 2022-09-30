#pragma once

#include "Rooms.h"
#include "gabrielGraph.h"
#include "delaunayGraph.h"
#include "relativeNeighborhoodGraph.h"
#include "mstGraph.h"
#include "Grid.h"
#include "Corridors.h"
#include "Walls.h"
#include "bspTree.h"

#include "SimpleIni.h"

class dungeonGenerator
{
private:

public:
	dungeonGenerator();
	~dungeonGenerator();

	BaseModule* currentModule;
	vector<BaseModule*> modulesInOrder;

	RoomGen* roomGenerator;
	BaseGraphGenerator* graphGenerator;
	BaseGraphSimplifier* graphSimplified;
	Grid* dungeonGrid;
	CorridorGen* corridorGenerator;
	WallGen* wallGenerator;
	BspTree* dungeonBspTree;

	int width, height;

	clock_t totalTime;
	int totalTimeSpent;

	// Generation seed
	unsigned int m_Seed;
	int generationMode;

	// Connected to step phases
	int currentlyRunning;
	int currentState;
	bool finishedGeneration;

	bool GenerateDirect();
	bool GenerateStep();
	void Reset();
};