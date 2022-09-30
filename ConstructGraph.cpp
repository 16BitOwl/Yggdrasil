#include "ConstructGraph.h"
#include "Rooms.h"

ConstructGraph::ConstructGraph()
{

}

ConstructGraph::~ConstructGraph()
{
	BaseGraph::~BaseGraph();
}

void ConstructGraph::Run()
{
	// Sanity checks
	if (simpleGraph->nodes.size() != completeGraph->nodes.size())
	{
		return;
	}

	// Check how many edges differ
	unsigned int amount = completeGraph->edges - simpleGraph->edges;
	if (amount / 0.3f < 0) // No point in even trying if there aren't enough edges
	{
		return;
	}

	// Copy simplified graph
	nodes = simpleGraph->nodes;
	edges = simpleGraph->edges;

	// Loop
	while (amount > 0)
	{
		// Choose random edge and check if it already exists
		//int rndNode = RandomInterval();

		// Decrease amount and proceed
		amount--;
	}
}