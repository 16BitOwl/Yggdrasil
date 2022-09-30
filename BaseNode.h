#pragma once

#include <vector>

#include "random.h"
#include "BaseModule.h"

using namespace std;

// Define a few classes and structs that are used in the code
class RoomGen;
class BaseRoom;
struct BaseNode;

/*!
* \struct GraphNeighbor
* \brief GraphNeighbor struct, stores information about a nodes neighbor and the weight between the neighbor and the node
*/
struct GraphNeighbor
{
	/*! 
	* \var BaseNode* node
    * \brief Pointer to the nodes neighbor
	*/
	BaseNode* node;

	/*! 
	* \var int weight
    * \brief The weight between the node and the neighbor
	*/
	int weight;

	GraphNeighbor() : node(NULL), weight(0) {}
	GraphNeighbor(BaseNode* _node, int _weight) : node(_node), weight(_weight) {}
};

/*!
* \struct BaseNode
* \brief BaseNode struct, stores information about a node in a graph, with neighbors and the room it currently handles
*/
struct BaseNode
{
	/*! 
	* \var vector<GraphNeighbor*> neighbors
    * \brief A vector of pointers to the node neighbors
	*/
	vector<GraphNeighbor*> neighbors;

	/*! 
	* \var vector<GraphNeighbor*> neighborsMST
    * \brief A vector of pointers to the node neighbors in a MST graph
	*/
	vector<GraphNeighbor*> neighborsMST;

	/*! 
	* \var BaseRoom* room
    * \brief Pointer to the nodes room data
	*/
	BaseRoom* room;
};

/*!
* \class BaseGraph
* \brief BaseGraph class, the lowest level graph module. Inherits from BaseModule
* \author Dennis Fredriksson
*
* The BaseGraph class handles the low level functions of any given graph, such as data handling and clearing said data. It also contains overloads for higher level graph classes
*/
class BaseGraph : public BaseModule
{
private:

public:
	/*!
	* \fn BaseGraph()
	* \brief Class constructor
	*/
	BaseGraph();

	/*!
	* \fn BaseGraph(BaseGraph& _copy)
	* \brief Class constructor
	*/
	BaseGraph(BaseGraph& _copy);

	/*!
	* \fn virtual ~BaseGraph()
	* \brief Class virtual deconstructor
	*/
	virtual ~BaseGraph();

	/*! 
	* \var unsigned int edges
    * \brief Amount of edges in the graph
	*/
	unsigned int edges;

	/*! 
	* \var vector<BaseNode*> nodes
    * \brief A vector of pointers to all the nodes in the graph
	*/
	vector<BaseNode*> nodes;

	virtual void Clear();
};

/*!
* \class BaseGraphGenerator
* \brief BaseGraphGenerator class, used by classes that generate graphs from various datasets. Inherits from BaseGraph
* \author Dennis Fredriksson
*
* The BaseGraphGenerator class is used by higher level classes that handle the generation of graphs from any given type of dataset.
*/
class BaseGraphGenerator : public BaseGraph
{
private:

public:
	/*!
	* \fn BaseGraphGenerator()
	* \brief Class constructor
	*/
	BaseGraphGenerator();

	/*!
	* \fn virtual ~BaseGraphGenerator()
	* \brief Class virtual deconstructor
	*/
	virtual ~BaseGraphGenerator();

	/*! 
	* \var RoomGen* rooms
    * \brief A point to the room generation module
	*/
	RoomGen* rooms;

	/*!
	* \fn virtual void SetRooms(RoomGen* _rooms)
	* \brief Stores the room generation module used by the graph generator
	* \param[RoomGen*] A pointer to the room generator module
	*/
	virtual void SetRooms(RoomGen* _rooms) { rooms = _rooms; }

	/*!
	* \fn virtual void AddEdge(Room* _left, Room* _right)
	* \brief Adds a new edge to the node graph
	* \param[BaseRoom*] A pointer to the left room in the edge
	* \param[BaseRoom*] A pointer to the right room in the edge
	*/
	virtual void AddEdge(BaseRoom* _left, BaseRoom* _right);
};

/*!
* \class BaseGraphSimplifier
* \brief BaseGraphSimplifier class, used by classes that simplify/reduce graphs. Inherits from BaseGraph
* \author Dennis Fredriksson
*
* The BaseGraphGenerator class is used by higher level classes that handle the simplification/reduction of larger graphs to smaller graphs
*/
class BaseGraphSimplifier : public BaseGraph
{
private:

public:
	/*!
	* \fn BaseGraphSimplifier()
	* \brief Class constructor
	*/
	BaseGraphSimplifier();

	/*!
	* \fn virtual ~BaseGraphSimplifier()
	* \brief Class virtual deconstructor
	*/
	virtual ~BaseGraphSimplifier();

	/*! 
	* \var BaseGraph* graph
    * \brief A point to a graph module
	*/
	BaseGraph* graph;

	/*!
	* \fn virtual void SetGraph(BaseGraph* _graph)
	* \brief Stores the graph module used by the graph simplifier 
	* \param[BaseGraph*] A pointer to the graph module
	*/
	virtual void SetGraph(BaseGraph* _graph) { graph = _graph; }
};