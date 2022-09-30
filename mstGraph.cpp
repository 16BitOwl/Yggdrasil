#include "mstGraph.h"
#include "dungeonGenerator.h"

MstGraph::MstGraph()
{
}

MstGraph::~MstGraph()
{
	BaseGraphSimplifier::~BaseGraphSimplifier();
}

void MstGraph::Run()
{
	// Run pre step setup
	PreStep();

	// Loop step until finished
	while (marked.size() < graph->nodes.size())
	{
		Step();
	}

	// Run post step checks
	PostStep();
}

void MstGraph::PreStep()
{
	// Clear previous data
	marked.clear();
		
	graph = generator->graphGenerator;
	finishedStep = false;

	// Select random start point
	nodes.push_back(new BaseNode(*graph->nodes[graph->nodes.size() - 1]));
	marked.push_back(graph->nodes[graph->nodes.size() - 1]->room);
}

void MstGraph::Step() 
{
	int lowestCost = INT_MAX;
	BaseNode* lowestNode;
	BaseNode* currentNode;

	// Look through the current MST for the lowest neighbor
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		for (unsigned int j = 0; j < nodes[i]->neighbors.size(); j++)
		{
			// Check for lowest cost! And it may not be marked already
			if (nodes[i]->neighbors[j]->weight <= lowestCost && find(marked.begin(), marked.end(), nodes[i]->neighbors[j]->node->room) == marked.end())
			{
				lowestCost = nodes[i]->neighbors[j]->weight;
				lowestNode = nodes[i]->neighbors[j]->node;
				currentNode = nodes[i];
			}
		}
	}

	// Add to marked, no matter what
	marked.push_back(lowestNode->room);

	// If not already added, include in new MST
	if (find(nodes.begin(), nodes.end(), lowestNode) == nodes.end()) 
	{
		nodes.push_back(new BaseNode(*lowestNode));

		GraphNeighbor* temp = new GraphNeighbor(lowestNode, lowestCost);
		currentNode->neighborsMST.push_back(temp);
		edges++;

		// Are we finished?
		if (edges == graph->nodes.size() - 1)
		{
			finishedStep = true;
		}
	}
}

void MstGraph::PostStep()
{
	// Copy new MST graph over the original
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->neighbors = nodes[i]->neighborsMST;
		nodes[i]->room->node = nodes[i];
	}
}