#pragma once

#include "SimpleIni.h"
#include "Rooms.h"
#include "Corridors.h"
#include "BaseModule.h"

#include <vector>

using namespace std;

/*!
* \enum CellType
* \brief CellType enum, describes the different cell types and their priority. Higher number = higher priority
*/
enum CellType
{
	EMPTY = 0,
	CORRIDOR,
	ROOM
};

/*!
* \struct GridCell
* \brief GridCell struct, stores information about a cell in the grid
*/
struct GridCell
{
	/*! 
	* \var CellType type
    * \brief Stores information about the cell type
	*/
	CellType type;

	GridCell() : type(EMPTY) {}
	GridCell(CellType _type) : type(_type) {}
};

/*!
* \struct GridRectInfo
* \brief GridRectInfo struct, stores information that is used in the grid conversion
*/
struct GridRectInfo
{
	/*! 
	* \var GridRect* rect
    * \brief Stores information about the rectangle that is to be converted to the grid
	*/
	GridRect* rect;

	/*! 
	* \var CellType type
    * \brief Stores information about the cell type
	*/
	CellType type;

	GridRectInfo() {}
	GridRectInfo(GridRect* _rect, CellType _type) : rect(_rect), type(_type) {}
};


/*!
* \class Grid
* \brief Grid class, converts shape data into a grid styled layout for further processing
* \author Dennis Fredriksson
*
* The Grid class converts shape data into a grid styled layout for further processing. 
*/
class Grid : public BaseModule
{
private:

public:
	/*!
	* \fn Grid()
	* \brief Class constructor
	*/
	Grid();

	/*!
	* \fn Grid(int _x, int _y, unsigned int _width, unsigned int _height, int _padding)
	* \brief Class constructor
	*/
	Grid(int _x, int _y, unsigned int _width, unsigned int _height, int _padding);

	/*!
	* \fn ~Grid()
	* \brief Class deconstructor
	*/
	~Grid();

	/*! 
	* \var GridCell** grid
    * \brief A double pointer, that is used for the grid
	*/
	GridCell** grid;

	/*! 
	* \var bool hasCells
    * \brief Used on clearing, to make sure there are any cells at all
	*/
	bool hasCells;

	/*! 
	* \var int x, y
    * \brief Stores the grid offset on XY-axis
	*/
	int x, y;

	/*! 
	* \var unsigned int width, height
    * \brief Stores the grid padding
	*/
	unsigned int width, height;

	/*! 
	* \var vector<GridRectInfo*> gridRectStorage
    * \brief A vector of pointers to the rectangles used by the grid coversion
	*/
	vector<GridRectInfo*> gridRectStorage;

	/*!
	* \fn void Setup(unsigned int _width, unsigned int _height)
	* \brief Inits the grid with the given height and width
	* \param[unsigned int] The grid width
	* \param[unsigned int] The grid height
	*/
	void Setup(unsigned int _width, unsigned int _height);

	/*!
	* \fn void Offset(int _x, int _y)
	* \brief Offsets the grid
	* \param[int] The grid offset on the X-axis
	* \param[int] The grid offset on the Y-axis
	*/
	void Offset(int _x, int _y);

	/*!
	* \fn bool ValidPosition(int _x, int _y)
	* \brief Check if the given XY-position is valid and within range
	* \param[int] The position on the X-axis
	* \param[int] The position on the Y-axis
	* \return bool
	*/
	bool ValidPosition(int _x, int _y);

	/*!
	* \fn void FromGridRect(GridRect* _gridRect, CellType _rectType)
	* \brief Add a new rectangle to the list of rectangles to be converted to the grid format
	* \param[GridRect*] The new rectangle
	* \param[CellType] The type of cell that should be used for the new grid rectangle
	*/
	void FromGridRect(GridRect* _gridRect, CellType _rectType);

	/*!
	* \fn void FromGridData(GridCell** _grid, int _x, int _y, int _width, int _height)
	* \brief Add a new rectangle to the list of rectangles to be converted to the grid format
	* \param[GridCell**] The grid data to be added
	* \param[int] The data offset on the X-axis
	* \param[int] The data offset on the Y-axis
	* \param[int] The data width
	* \param[int] The data height
	*/
	void FromGridData(GridCell** _grid, int _x, int _y, int _width, int _height);

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