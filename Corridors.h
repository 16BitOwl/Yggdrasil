#pragma  once

#include <vector>

#include "SimpleIni.h"
#include "BaseNode.h"
#include "BaseModule.h"
#include "Rooms.h"

using namespace std;

/*!
* \struct Corridor
* \brief Corridor struct, stores  information about the corridor shape and the possible grid blocks
*/
struct Corridor
{
	/*! 
	* \var BaseNode* leftRoom,* rightRoom
    * \brief Stores pointers to the two rooms connected by this corridor
	*/
	BaseNode* leftRoom,* rightRoom;

	/*! 
	* \var vector<GridRect*> blocks
    * \brief A vector of pointers to possible grid blocks for this corridor
	*/
	vector<GridRect*> blocks;

	/*! 
	* \var int line1x1, line1y1, line1x2, line1y2
    * \brief Stores the first line of the L-shape
	*/
	int line1x1, line1y1, line1x2, line1y2;

	/*! 
	* \var int line2x1, line2y1, line2x2, line2y2
    * \brief Stores the second line of the L-shape
	*/
	int line2x1, line2y1, line2x2, line2y2;
};

/*!
* \class CorridorGen
* \brief CorridorGen class, used in the generation of corridors
* \author Dennis Fredriksson
*
* The CorridorGen class is used to generate a set of corridors between the various rooms, using a graph to define the connections between the rooms.
*/
class CorridorGen : public BaseModule
{
private:
	unsigned int primary;

	/*!
	* \fn void GenerateCorridorBlocksVertical(int _x, int _y, int _height, Corridor& _corridor)
	* \brief Generates possible grid cells and stores them internally
	* \param[int] The start on the X-axis
	* \param[int] The start on the Y-axis
	* \param[int] The height of the corridor
	* \param[Corridor&] The reference to the corridor that needs to be altered
	* \private
	*/
	void GenerateCorridorBlocksVertical(int _x, int _y, int _height, Corridor& _corridor);

	/*!
	* \fn void GenerateCorridorBlocksHorizontal(int _x, int _y, int _width, Corridor& _corridor)
	* \brief Generates possible grid cells and stores them internally
	* \param[int] The start on the X-axis
	* \param[int] The start on the Y-axis
	* \param[int] The width of the corridor
	* \param[Corridor&] The reference to the corridor that needs to be altered
	* \private
	*/
	void GenerateCorridorBlocksHorizontal(int _x, int _y, int _width, Corridor& _corridor);

	/*!
	* \fn bool Plot(int _x, int _y, Corridor& _corridor)
	* \brief Generates possible grid cells and stores them internally
	* \param[int] The plot on the X-axis
	* \param[int] The plot on the Y-axis
	* \param[Corridor&] The reference to the corridor that needs to be altered
	* \private
	*/
	bool Plot(int _x, int _y, Corridor& _corridor);

public:
	/*!
	* \fn CorridorGen()
	* \brief Class constructor
	*/
	CorridorGen();

	/*!
	* \fn virtual ~CorridorGen()
	* \brief Class deconstructor
	*/
	~CorridorGen();

	/*! 
	* \var BaseGraph* graph
    * \brief A point to a graph module
	*/
	BaseGraph* graph;

	/*! 
	* \var vector<Corridor*> corridors
    * \brief A vector of pointers to the resulting corridors generated
	*/
	vector<Corridor*> corridors;

	/*! 
	* \var int corridorWidth
    * \brief External config, stores the width of the corridors
	*/
	int corridorWidth;

	/*! 
	* \var int ratioAlgorithms
    * \brief External config, is used to set ration between L-shapes and Bresenham's
	*/
	int ratioAlgorithms;

	/*! 
	* \var unsigned int width, height
    * \brief Stores the total width and height of the generated corridors
	*/
	unsigned int width, height;

	/*!
	* \fn void SetGraph(BaseGraph* _graph)
	* \brief Stores the graph module used by the generation process 
	* \param[BaseGraph*] A pointer to the graph module
	*/
	void SetGraph(BaseGraph* _graph) { graph = _graph; }

	/*!
	* \fn void GetSize(int& _width, int& _height
	* \brief Checks the width/height and returns proper values
	* \param[int&] The width to check and return
	* \param[int&] The height to check and return
	*/
	void GetSize(int& _width, int& _height);

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