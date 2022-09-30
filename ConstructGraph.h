#pragma once

#include "baseNode.h"

/*!
* \class ConstructGraph
* \brief ConstructGraph class, a graph generation algorithm that combines a complete graph and a simplified graph
* \author Dennis Fredriksson
*
* The ConstructGraph class 
*/
class ConstructGraph : public BaseGraph
{
private:

public:
	/*!
	* \fn ConstructGraph()
	* \brief Class constructor
	*/
	ConstructGraph();

	/*!
	* \fn virtual ~ConstructGraph()
	* \brief Class deconstructor
	*/
	~ConstructGraph();

	BaseGraph* simpleGraph;
	BaseGraph* completeGraph;

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
	void Step() {}
	
	/*!
	* \fn void PreStep()
	* \brief Overload function, used before the step by step generation starts
	*/
	void PreStep(dungeonGenerator* _generator) {}
	
	/*!
	* \fn void PostStep()
	* \brief Overload function, used after the step by step generation finishes
	*/
	void PostStep() {}
};