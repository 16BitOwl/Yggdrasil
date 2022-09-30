#pragma once

#include <vector>

using namespace std;

class dungeonGenerator;

/*!
* \struct GridRect
* \brief GridRect struct, stores basic information about rectangular shapes in the grid system and/or for other uses
*/
struct GridRect
{
	int x1, y1, x2, y2;
	unsigned int width, height;

	GridRect() : x1(0), y1(0), x2(0), y2(0), width(0), height(0) {}
	GridRect(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2), width(1), height(1) {}
};

/*!
* \class BaseModule
* \brief BaseModule class, the lowest level inheritance of the generator framework
* \author Dennis Fredriksson
*
* The BaseModule class itself doesn't do much, other than to define functions which must be implemented(to a certain degree) by each module in the framework. 
* These functions are then called by the generator at runtime, in a predetermined order outlined in the config files.
*/
class BaseModule
{
private:

public:
	/*!
	* \fn BaseModule()
	* \brief Class constructor
	*/
	BaseModule();

	/*!
	* \fn virtual ~BaseModule()
	* \brief Class virtual deconstructor
	*/
	virtual ~BaseModule();

	/*! 
	* \var BaseModule* parent
    * \brief Pointer to the module parent. Null means root module
	*/
	BaseModule* parent;

	/*! 
	* \var vector<BaseModule*> children
    * \brief Vector of pointers to the module children
	*/
	vector<BaseModule*> children;

	/*! 
	* \var bool finishedStep
    * \brief A boolean that stores the current step state
	*/
	bool finishedStep;

	dungeonGenerator* generator;

	/*!
	* \fn virtual void Clear() = 0
	* \brief Virtual function that is designed to clear all module data
	*/
	virtual void Clear() = 0;

	/*!
	* \fn virtual void LoadData() = 0
	* \brief Virtual function that is designed to load external config data for the module
	*/
	virtual void LoadData() = 0;

	/*!
	* \fn virtual void Run() = 0
	* \brief Virtual function that is used to run the module code
	*/
	virtual void Run() = 0;

	/*!
	* \fn virtual void PreStep() = 0
	* \brief Virtual function that is used to preform step by step generation. This is run before the steps start
	*/
	virtual void PreStep() = 0;

	/*!
	* \fn virtual void Step() = 0
	* \brief Virtual function that is used to preform step by step generation. This is run once each frame until done
	*/
	virtual void Step() = 0;

	/*!
	* \fn virtual void Step() = 0
	* \brief Virtual function that is used to preform step by step generation.  This is run after the steps finish
	*/
	virtual void PostStep() = 0;
};