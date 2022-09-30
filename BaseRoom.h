#pragma once

#include <vector>

#include "BaseModule.h"
#include "BaseNode.h"
#include "SimpleIni.h"

using namespace std;

struct GridCell;

/*!
* \struct Portal
* \brief Portal struct, stores information about portals for the rooms
*/
struct Portal
{
	/*! 
	* \var int x, y
    * \brief The portal position on the XY-axis, relative to the room
	*/
	int x, y;

	Portal(int _x, int _y) : x(_x), y(_y) {}
	Portal() {}
};

/*!
* \class BaseRoom
* \brief BaseRoom class, storage containers for room information and generation
* \author Dennis Fredriksson
*
* The BaseRoom class is used by the room generation process to store the finalized rooms, as well as any information related to generating the room itself
*/
class BaseRoom
{
private:

public:
	/*!
	* \fn BaseRoom()
	* \brief Class constructor
	*/
	BaseRoom();

	/*!
	* \fn virtual ~BaseRoom()
	* \brief Class virtual deconstructor
	*/
	virtual ~BaseRoom();

	/*!
	* \fn void Setup(unsigned int _width, unsigned int _height)
	* \brief Inits the room grid
	* \param[unsigned int] The width of the room grid
	* \param[unsigned int] The height of the room grid
	*/
	void Setup(unsigned int _width, unsigned int _height);

	/*! 
	* \var GridCell** grid
    * \brief A double pointer, that is used for the room design grid
	*/
	GridCell** grid;

	/*! 
	* \var bool hasCells
    * \brief Used on clearing, to make sure there are any cells at all
	*/
	bool hasCells;

	/*! 
	* \var unsigned int width, height
    * \brief The total size of the room, width and height
	*/
	unsigned int width, height;

	/*! 
	* \var unsigned int area
    * \brief The total area used by the room
	*/
	unsigned int area;

	/*! 
	* \var float radius
    * \brief The room collision avoidance radius
	*/
	float radius;

	/*! 
	* \var int centerX, centerY
    * \brief The center of the room on the XY-axis
	*/
	int centerX, centerY;

	/*! 
	* \var int x1, y1, x2, y2
    * \brief The XY-axis storage for the entire required space of the room
	*/
	int x1, y1, x2, y2;

	/*! 
	* \var BaseNode* node
    * \brief A pointer to a node in a graph that handles room connectivity
	*/
	BaseNode* node;

	/*! 
	* \var vector<Portal*> portals
    * \brief A vector of pointers to the possible room portals
	*/
	vector<Portal*> portals;

	/*! 
	* \var string name
    * \brief The name of the room
	*/
	string name;
};

class BasePrefab
{
private:

public:
		/*!
	* \fn BasePrefab()
	* \brief Class constructor
	*/
	BasePrefab();

	/*!
	* \fn virtual ~BasePrefab()
	* \brief Class virtual deconstructor
	*/
	virtual ~BasePrefab();

	/*!
	* \fn void LoadSettings(string _name, string _file)
	* \brief Loads prefab settings from an external file
	* \param[string] The prefab name
	* \param[string] The file path, relative to the program default folder
	*/
	void LoadSettings(string _name, string _file);

	/*! 
	* \var vector<string> prefabDataFormatted
    * \brief A vector of formatted strings loaded from the prefab file
	*/
	vector<string> prefabDataFormatted;

	/*! 
	* \var bool isRequired
    * \brief External config, is this prefab room required by any given dungeon?
	*/
	bool isRequired;

	/*! 
	* \var string name
    * \brief External config, the prefab name
	*/
	string name;

	/*! 
	* \var int amount
    * \brief External config, how many of these rooms should be created if required
	*/
	int amount;

	/*! 
	* \var string filename
    * \brief External config, the prefab filename
	*/
	string filename;

	/*! 
	* \var string layoutPath
    * \brief External config, the prefab layout filename
	*/
	string layoutPath;

	/*! 
	* \var int locationMode
    * \brief External config, what layout position mode should be used at generation
	*/
	int locationMode;

	/*! 
	* \var int desiredX, desiredY
    * \brief External config, the desired spawn location on XY-axis
	*/
	int desiredX, desiredY;

	/*! 
	* \var float radius
    * \brief External config, a circle radius used by various spawning modes
	*/
	float radius;

	/*! 
	* \var float roomRadius
    * \brief External config, a predetermined radius for a prefab room
	*/
	float roomRadius;

	/*! 
	* \var string relatedRoom
    * \brief External config, a room which is related to this one, usually for spacing 
	*/
	string relatedRoom;
};