#include "BaseRoom.h"
#include "Grid.h"

//////////////////////////////////////////////////////////////////////////
// Code for the BaseRoom
//////////////////////////////////////////////////////////////////////////

BaseRoom::BaseRoom()
{
	node = NULL;
	grid = NULL;
	hasCells = false;
}

BaseRoom::~BaseRoom()
{
	// Clear grid
	if (hasCells)
	{
		for (unsigned int i = 0; i < width; i++)
		{
			delete[] grid[i];
		}
		delete[] grid;
	}
}

void BaseRoom::Setup(unsigned int _width, unsigned int _height)
{
	// Create dungeon grid
	grid = new GridCell*[_width];
	for (unsigned int i = 0; i < _width; i++)
	{
		grid[i] = new GridCell[_height];
	}

	width = _width;
	height = _height;
}

//////////////////////////////////////////////////////////////////////////
// Code for the BasePrefab
//////////////////////////////////////////////////////////////////////////

BasePrefab::BasePrefab()
{

}

BasePrefab::~BasePrefab()
{

}

void BasePrefab::LoadSettings(string _name, string _file)
{
	// Temp
	char charBuffer[256];
	CSimpleIniA prefabReader;

	// Load basic data
	name = _name;
	filename = _file;

	// Read the INI file
	prefabReader.SetUnicode();
	prefabReader.LoadFile(filename.c_str());

	// Read layout file path
	layoutPath = prefabReader.GetValue("Prefab", "Layout");
	isRequired = prefabReader.GetBoolValue("Prefab", "Required", false);
	amount = (int)prefabReader.GetDoubleValue("Prefab", "Amount", 0);

	locationMode = (int)prefabReader.GetDoubleValue("Layout", "Mode", 0);
	desiredX = (int)prefabReader.GetDoubleValue("Layout", "DesiredX", 0);
	desiredY = (int)prefabReader.GetDoubleValue("Layout", "DesiredY", 0);
	radius = (float)prefabReader.GetDoubleValue("Layout", "Radius", 0);
	relatedRoom = prefabReader.GetValue("Layout", "RelatedRoom", "NONE");

	roomRadius = (float)prefabReader.GetDoubleValue("Room", "Radius", 0);

	// Read layout file
	fstream file;
	file.open(layoutPath, fstream::in);
	while(!file.eof())
	{
		file.getline(charBuffer, 256);
		prefabDataFormatted.push_back(charBuffer);
	}
	file.close();
}