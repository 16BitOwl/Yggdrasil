#pragma once

#include <algorithm>

#include "baseNode.h"

/*!
* \class MstGraph
* \brief MstGraph class, a graph simplification algorithm for any given base graph
* \author Dennis Fredriksson
*
* The MstGraph class is used to remove redundant edges and to create a non-looping graph. It keeps all edges with the lowest weights and removes all others. 
* Beware that this algorithm is greedy and does not have a linear relation between time and the amount of points.
*/
class MstGraph : public BaseGraphSimplifier
{
private:
	vector<BaseRoom*> marked;

public:
	/*!
	* \fn MstGraph()
	* \brief Class constructor
	*/
	MstGraph();

	/*!
	* \fn virtual ~MstGraph()
	* \brief Class deconstructor
	*/
	~MstGraph();

	// ======= Base module overloads =======

	/*!
	* \fn void LoadData()
	* \brief Overload function, used to load in external config data
	*/
	void LoadData() {}

	/*!
	* \fn void Run()
	* \brief Overload function, used to preform the graph generation
	*/
	void Run();

	/*!
	* \fn void Step()
	* \brief Overload function, used to preform a step by step graph generation over a series of frames
	*/
	void Step();

	/*!
	* \fn void PreStep()
	* \brief Overload function, used before the step by step generation starts
	*/
	void PreStep();

	/*!
	* \fn void PostStep()
	* \brief Overload function, used after the step by step generation finishes
	*/
	void PostStep();
};