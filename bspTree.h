#pragma once

#include <vector>
#include <stdio.h>
#include <stdlib.h> 

#include "SimpleIni.h"
#include "Rooms.h"
#include "BaseModule.h"

using namespace std;

/*!
* \class BspTree
* \brief BspTree class, handles optimization for various other modules
* \author Dennis Fredriksson
*
* The BspTree class is used to create a quad tree structure used by many modules in optimization issues.
*/
class BspTree : public BaseModule
{
private:

public:
	/*!
	* \fn BspTree()
	* \brief Class constructor
	*/
	BspTree();

	/*!
	* \fn BspTree(int _x, int _y, int _width, int _height, int _minLeafSize, BspTree* _parent)
	* \brief Class constructor
	*/
	BspTree(int _x, int _y, int _width, int _height, int _minLeafSize, BspTree* _parent);

	/*!
	* \fn virtual ~BspTree()
	* \brief Class deconstructor
	*/
	~BspTree();

	/*! 
	* \var BspTree* leftChild
    * \brief Pointer to the left leaf child
	*/
	BspTree* leftChild;

	/*! 
	* \var BspTree* rightChild
    * \brief Pointer to the right leaf child
	*/
	BspTree* rightChild;

	/*! 
	* \var BspTree* parent
    * \brief Pointer to the leaf parent. Null means root leaf
	*/
	BspTree* parent;

	/*! 
	* \var int minimumLeafSize
    * \brief The smallest height or width of a leaf
	*/
	int minimumLeafSize;

	/*! 
	* \var vector<BaseRoom*> rooms
    * \brief A vector of pointers to each room inside of this leaf
	*/
	vector<BaseRoom*> rooms;

	// The position and size of this Leaf
	int y, x, width, height;

	/*!
	* \fn bool Split()
	* \brief Preforms a split on the current leaf and creates two new sub leaves
	* \return bool
	*/
	bool Split();

	// ======= Base module overloads =======
	
	/*!
	* \fn void Clear()
	* \brief Overload function, used to reset all data in the module
	* Deletes any child leaves and then delete itself. It is recommended that this is ONLY done on the root leaf, as it removes the entire tree
	*/
	void Clear();
		
	/*!
	* \fn void LoadData()
	* \brief Overload function, used to load in external config data
	*/
	void LoadData();
		
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