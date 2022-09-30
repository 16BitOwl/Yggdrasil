#pragma once

#include "baseNode.h"

/*!
* \class DelaunayGraph
* \brief DelaunayGraph class, a graph generation algorithm for a set of points in 2D space
* \author Dennis Fredriksson
*
* The DelaunayGraph class is used to create a looping graph out of a given set of points in 2D space. The algorithm uses 3 points at any given time to create triangles(and edges).
* Beware that this algorithm is greedy and does not have a linear relation between time and the amount of points.
*/
class DelaunayGraph : public BaseGraphGenerator
{
private:
	unsigned int primary, secondary;

public:
	/*!
	* \fn DelaunayGraph()
	* \brief Class constructor
	*/
	DelaunayGraph();

	/*!
	* \fn virtual ~DelaunayGraph()
	* \brief Class deconstructor
	*/
	~DelaunayGraph();

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