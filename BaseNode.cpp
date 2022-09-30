#include "baseNode.h"
#include "Rooms.h"
#include "BaseRoom.h"

// ======================================================================================
// = Base graph class
// ======================================================================================
BaseGraph::BaseGraph()
{
	edges = 0;
}

BaseGraph::BaseGraph(BaseGraph& _copy)
{
	edges = _copy.edges;
	nodes = _copy.nodes;
}

BaseGraph::~BaseGraph()
{
	BaseModule::~BaseModule();
}

void BaseGraph::Clear()
{
	edges = 0;

	// Clean up nodes
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->neighbors.clear();
	}
	nodes.clear();
}

// ======================================================================================
// = Base graph generator class
// ======================================================================================
BaseGraphGenerator::BaseGraphGenerator()
{

}

BaseGraphGenerator::~BaseGraphGenerator()
{
	BaseGraph::~BaseGraph();
}

void BaseGraphGenerator::AddEdge(BaseRoom* _left, BaseRoom* _right)
{
	// Find distance, for weight
	int odistance = (int)Distance2D(_left->centerX, _left->centerY, _right->centerX, _right->centerY) + 0.5f;

	if (_left->node == NULL) // Make sure the room has a node 
	{
		BaseNode* tNode = new BaseNode();
		tNode->room = _left;
		_left->node = tNode;

		nodes.push_back(tNode);
	}

	if (_right->node == NULL)// Make sure the room has a node 
	{
		BaseNode* tNode = new BaseNode();
		tNode->room = _right;
		_right->node = tNode;

		nodes.push_back(tNode);
	}

	_left->node->neighbors.push_back(new GraphNeighbor(_right->node, odistance));
	_right->node->neighbors.push_back(new GraphNeighbor(_left->node, odistance));

	edges++;
}

// ======================================================================================
// = Base graph simplifier class
// ======================================================================================
BaseGraphSimplifier::BaseGraphSimplifier()
{

}

BaseGraphSimplifier::~BaseGraphSimplifier()
{
	BaseGraph::~BaseGraph();
}