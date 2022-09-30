#pragma once

#include "SimpleIni.h"
#include "Grid.h"
#include "BaseModule.h"

#include <vector>

using namespace std;

/*!
* \struct WallData
* \brief WallData struct, stores information about walls(based on grid data)
*/
struct WallData
{
	/*! 
	* \var int x1, y1, x2, y2
    * \brief Stores data about the wall in the form of a line
	*/
	int x1, y1, x2, y2;

	WallData() : x1(0), y1(0), x2(0), y2(0) {}
};

/*!
* \class WallGen
* \brief WallGen class, 
* \author Dennis Fredriksson
*
* The WallGen class
*/
class WallGen : public BaseModule
{
private:
	unsigned int primary;

public:
	/*!
	* \fn WallGen()
	* \brief Class constructor
	*/
	WallGen();

	/*!
	* \fn ~WallGen()
	* \brief Class deconstructor
	*/
	~WallGen();

	/*! 
	* \var vector<WallData*> walls
    * \brief A vector of pointers to the resulting walls
	*/
	vector<WallData*> walls;

	/*! 
	* \var Grid* grid
    * \brief Stores the grid to be used in the generation process
	*/
	Grid* grid;

	/*!
	* \fn void SetGrid(Grid* _grid)
	* \brief Sets which grid to be used in the wall generation process
	* \param[Grid*] The grid to be used
	*/
	void SetGrid(Grid* _grid) { grid = _grid; }

	// ======= Base module overloads =======
	
	/*!
	* \fn void Clear()
	* \brief Overload function, used to reset all data in the module
	*/
	void Clear();
		
	/*!
	* \fn void LoadData()
	* \brief Overload function, used to load in external config data
	*/
	void LoadData() {}
		
	/*!
	* \fn void Run()
	* \brief Overload function, used to preform the modules task
	*/
	void Run();
		
	/*!
	* \fn void Step()
	* \brief Overload function, used to preform the modules task step by step over a series of frames
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