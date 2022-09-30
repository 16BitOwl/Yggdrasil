#pragma once

#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "BaseRoom.h"
#include "SimpleIni.h"
#include "baseNode.h"
#include "BaseModule.h"

#include "random.h"

using namespace std;

/*!
* \class RoomGen
* \brief RoomGen class, used to generate rooms
* \author Dennis Fredriksson
*
* The RoomGen class is used to generate a given amount of rooms for the dungeon. It also handles portals and layouts.
*/
class RoomGen : public BaseModule
{
private:
	/*! 
	* \var int minArea, maxArea
    * \brief External config, controls min/max room area allowed
	*/
	int minArea, maxArea;

	/*! 
	* \var int multArea
    * \brief External config, area multiplier for the Gaussian randomization
	*/
	int multArea;

	/*! 
	* \var double minRatio, maxRatio
    * \brief External config, controls min/max ration between room width/height
	*/
	double minRatio, maxRatio;

	/*! 
	* \var int minHeight, minWidth
    * \brief External config, controls min room width/height
	*/
	int minHeight, minWidth;

	/*! 
	* \var int maxHeight, maxWidth
    * \brief External config, controls max room width/height
	*/
	int maxHeight, maxWidth;

	/*! 
	* \var float spacingX, spacingY
    * \brief External config, sets the room spacing multiplier
	*/
	float spacingX, spacingY;

	/*! 
	* \var int amountRooms
    * \brief External config, sets the amount of rooms to generate
	*/
	int amountRooms;

	/*! 
	* \var int amountPrefabs
    * \brief External config, the amount of prefabs the generator has
	*/
	int amountPrefabs;

public:
	/*!
	* \fn RoomGen()
	* \brief Class constructor
	*/
	RoomGen();

	/*!
	* \fn ~RoomGen()
	* \brief Class deconstructor
	*/
	~RoomGen();

	/*! 
	* \var vector<BaseRoom*> rooms
    * \brief A vector of pointers to all the rooms generated
	*/
	vector<BaseRoom*> rooms;

	/*! 
	* \var vector<BasePrefab*> prefabs
    * \brief A vector of pointers to all the prefab rooms loaded
	*/
	vector<BasePrefab*> prefabs;

	/*! 
	* \var vector<BasePrefab*> firstToGenerate
    * \brief A vector of pointers that stores the prefabs that are to be generated before ANYTHING ELSE
	*/
	vector<BasePrefab*> firstToGenerate;

	/*! 
	* \var unsigned int width, height
    * \brief Stores the total width and height of the generated rooms
	*/
	unsigned int width, height;

	/*! 
	* \var int left, right, top, bottom
    * \brief Stores the left, right, top and bottom values based on min/max of the rooms
	*/
	int left, right, top, bottom;

	/*! 
	* \var int startX, startY
    * \brief Stores the start position of the generation on the XY-axis
	*/
	int startX, startY;

	/*!
	* \fn void GetSize(int& _width, int& _height
	* \brief Checks the width/height and returns proper values
	* \param[int&] The width to check and return
	* \param[int&] The height to check and return
	*/
	void GetSize(int& _width, int& _height);

	/*!
	* \fn void RandomRoom()
	* \brief Generates a random room
	*/
	void RandomRoom();

	/*!
	* \fn void PrefabRoom()
	* \brief Generates a prefab room
	*/
	void PrefabRoom();

	/*!
	* \fn void FindRoomPosition(BaseRoom* _room, int _mode = 0, BasePrefab* _prefab = NULL)
	* \brief Returns a location for the assigned room, using a specific placement mode
	* \param[BaseRoom*] The room that needs a location
	* \param[int] Outlines which placement mode should be used
	* \param[BasePrefab*] The prefab data used in all modes except mode 0
	*/
	void FindRoomPosition(BaseRoom* _room, int _mode = 0, BasePrefab* _prefab = NULL);

	/*!
	* \fn void DungeonSize(BaseRoom* _room)
	* \brief Calculates the new dungeon size
	* \param[BaseRoom*] The room that could change the size (left, top, bottom, right)
	*/
	void DungeonSize(BaseRoom* _room);

	bool CheckRoomOverlap(BaseRoom* _room, int _x, int _y);

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