#include "dungeonGenerator.h"

dungeonGenerator::dungeonGenerator()
{
	roomGenerator = new RoomGen();
	graphGenerator = new GabrielGraph();
	graphSimplified = new MstGraph();
	corridorGenerator = new CorridorGen();
	dungeonGrid = new Grid();
	wallGenerator = new WallGen();
	dungeonBspTree = new BspTree();

	width = height = 0;
	currentlyRunning = 0;
	currentState = 0;
	finishedGeneration = false;
	generationMode = 0;
}

dungeonGenerator::~dungeonGenerator()
{
	// Delete generators
	for (unsigned int i = 0; i < modulesInOrder.size(); i++)
	{
		delete modulesInOrder[i];
	}
	modulesInOrder.clear();
}

void dungeonGenerator::Reset()
{
	// Start time
	totalTimeSpent = 0;
	totalTime = clock();

	// Load settings
	CSimpleIniA iniReader;

	// Load settings file
	iniReader.SetUnicode();
	iniReader.LoadFile("dungeon.ini");

	// Seed!
	m_Seed = (unsigned int)iniReader.GetDoubleValue("General", "Seed", 0); // Seed
	if (m_Seed == 0)
	{
		m_Seed = static_cast<unsigned>(time(NULL));
	}
	srand(m_Seed);
	
	// Nasty hack to make sure rand() works properly	
	rand();
	rand();
	rand();
	rand();

	// Get generation mode
	generationMode = (int)iniReader.GetDoubleValue("General", "Mode", 0);

	// Setup module stack
	modulesInOrder.clear();
	modulesInOrder.push_back(roomGenerator);
	modulesInOrder.push_back(graphGenerator);
	modulesInOrder.push_back(graphSimplified);
	modulesInOrder.push_back(corridorGenerator);
	modulesInOrder.push_back(dungeonGrid);
	modulesInOrder.push_back(wallGenerator);
	modulesInOrder.push_back(dungeonBspTree);

	// Clear any previous steps and load data
	for (unsigned int i = 0; i < modulesInOrder.size(); i++)
	{
		modulesInOrder[i]->Clear();
		modulesInOrder[i]->LoadData();
		modulesInOrder[i]->generator = this;
	}

	// Reset general dungeon data
	width = height = 0;
	currentlyRunning = 0;
	currentState = 0;
	finishedGeneration = false;
}

bool dungeonGenerator::GenerateDirect()
{
	// Run all generators
	for (unsigned int i = 0; i < modulesInOrder.size(); i++)
	{
		modulesInOrder[i]->Run();
	}

	// Stop time
	totalTimeSpent = (int)((clock() - totalTime) / (double)(CLOCKS_PER_SEC / 1000));
	currentlyRunning = 6;

	return true;
}

bool dungeonGenerator::GenerateStep()
{
	if (finishedGeneration)
	{
		return true;
	}

	// Run pre step for module
	if (currentState == 0)
	{
		modulesInOrder[currentlyRunning]->PreStep();
		currentState = 1;
	}

	// Run step by step generation for module
	if (currentState == 1)
	{
		modulesInOrder[currentlyRunning]->Step();
		if (modulesInOrder[currentlyRunning]->finishedStep == true)
		{
			currentState = 2;
		}
	}

	// Run post step for module
	if (currentState == 2)
	{
		modulesInOrder[currentlyRunning]->PostStep();
		currentState = 0;

		// Go to next module
		currentlyRunning++;
		if (currentlyRunning >= modulesInOrder.size())
		{
			finishedGeneration = true;

			// Stop time
			totalTimeSpent = (int)((clock() - totalTime) / (double)(CLOCKS_PER_SEC / 1000));
		}
	}

	return finishedGeneration;
}