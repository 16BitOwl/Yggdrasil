#include "Rooms.h"
#include "dungeonGenerator.h"

RoomGen::RoomGen()
{
	startX = startY = 60;
}

RoomGen::~RoomGen()
{
}

void RoomGen::LoadData()
{
	CSimpleIniA iniReader;

	// Load settings file
	iniReader.SetUnicode();
	iniReader.LoadFile("dungeon.ini");

	amountRooms = (int)iniReader.GetDoubleValue("Rooms", "Amount", 100); // Amount of rooms

	multArea = (int)iniReader.GetDoubleValue("Rooms", "MultArea", 10); // Room area multiplier
	minArea = (int)iniReader.GetDoubleValue("Rooms", "MinArea", 4); // Minimum area of a room
	maxArea = (int)iniReader.GetDoubleValue("Rooms", "MaxArea", 30); // Maximum area of a room
	minHeight = (int)iniReader.GetDoubleValue("Rooms", "MinHeight", 2); // Minimum height of a room
	minWidth = (int)iniReader.GetDoubleValue("Rooms", "MinWidth", 2); // Minimum width of a room
	maxHeight = (int)iniReader.GetDoubleValue("Rooms", "MaxHeight", 10); // Maximum height of a room
	maxWidth = (int)iniReader.GetDoubleValue("Rooms", "MaxWidth", 10); // Maximum width of a room
	minRatio = iniReader.GetDoubleValue("Rooms", "MinRatio", 0.75); // Room minimum width/height ratio
	maxRatio = iniReader.GetDoubleValue("Rooms", "MaxRatio", 0.5); // Room maximum width/height ratio

	spacingX = (float)iniReader.GetDoubleValue("Layout", "MultSpacingX", 1);
	spacingY = (float)iniReader.GetDoubleValue("Layout", "MultSpacingY", 1);

	// Load all prefab rooms
	amountPrefabs = (int)iniReader.GetDoubleValue("Prefabs", "Amount", 0); // Amount of prefabs to load
	char charBuffer[256];
	for (int i = 0; i < amountPrefabs; i++)
	{
		// Load basic data
		sprintf(charBuffer, "PrefabName%d", i);
		string name = iniReader.GetValue("Prefabs", charBuffer);
		sprintf(charBuffer, "Prefab%d", i);
		string file = iniReader.GetValue("Prefabs", charBuffer);

		// Load settings externally
		BasePrefab* newPrefab = new BasePrefab();
		newPrefab->LoadSettings(name, file);

		// Store loaded data
		prefabs.push_back(newPrefab);
	}
}

void RoomGen::Run()
{
	// Run pre step setup
	PreStep();

	// Loop step until finished
	while (finishedStep == false)
	{
		Step();
	}

	// Run post step checks
	PostStep();
}

void RoomGen::PreStep()
{
	finishedStep = false;

	// Check the prefabs and mark any that is required and/or have special requirements as to layout or similar
	// Any room marked is generated before all other generation takes place
	for (unsigned int i = 0; i < prefabs.size(); i++)
	{
		// Is it required?
		if (prefabs[i]->isRequired)
		{
			firstToGenerate.push_back(prefabs[i]);
		}
	}
}

void RoomGen::Step()
{
	// We have finished generating rooms now!
	if (rooms.size() >= amountRooms)
	{
		finishedStep = true;
		return;
	}

	// Any rooms left if the prefab must list?
	if (firstToGenerate.size() > 0)
	{
		PrefabRoom();
		return;
	}

	// Create totally random room
	RandomRoom();
}

void RoomGen::PostStep()
{
	// Reset room position on XY-axis to [0, 0]
	for (unsigned int i = 0; i < rooms.size(); i++)
	{
		rooms[i]->centerX -= left;
		rooms[i]->centerY -= top;

		rooms[i]->x1 -= left;
		rooms[i]->x2 -= left;
		rooms[i]->y1 -= top;
		rooms[i]->y2 -= top;

		for (unsigned int j = 0; j < rooms[i]->portals.size(); j++)
		{
			rooms[i]->portals[j]->x -= left;
			rooms[i]->portals[j]->y -= top;
		}
	}

	// Find dungeon size
	width = right - left;
	height = bottom - top;

	GetSize(generator->width, generator->height);
}

void RoomGen::Clear()
{
	rooms.clear();
	prefabs.clear();
	firstToGenerate.clear();

	// For future size purposes
	left = top = INT_MAX;
	right = bottom = -INT_MAX;
	width = height = 0;
}

void RoomGen::GetSize(int& _width, int& _height)
{
	if (_width < width)
	{
		_width = width;
	}
	if (_height < height)
	{
		_height = height;
	}
}

void RoomGen::PrefabRoom()
{
	BaseRoom* temp = new BaseRoom();

	// Firstly, any rooms left in the prefab must list?
	if (firstToGenerate.size() > 0)
	{
		// Get some misc size info
		temp->width = firstToGenerate[0]->prefabDataFormatted[0].length();
		temp->height = firstToGenerate[0]->prefabDataFormatted.size();
		temp->area = temp->width * temp->height;
		temp->name = firstToGenerate[0]->name;
		temp->radius = firstToGenerate[0]->roomRadius;
		if (temp->radius == 0) // If no preset size, find distance
		{
			temp->radius = Distance2D(0.f, 0.f, temp->width / 2.f, temp->height / 2.f);
		}
		temp->Setup(temp->width, temp->height);

		// Find position
		FindRoomPosition(temp, firstToGenerate[0]->locationMode, firstToGenerate[0]);

		// Parse the layout data
		for (unsigned int i = 0; i < temp->width; i++)
		{
			for (unsigned int j = 0; j < temp->height; j++)
			{
				// Floor
				if (firstToGenerate[0]->prefabDataFormatted[i][j] == 'F')
				{
					temp->grid[i][j] = ROOM;
				}

				// Portal
				if (firstToGenerate[0]->prefabDataFormatted[i][j] == 'P')
				{
					temp->portals.push_back(new Portal(i + temp->x1, j + temp->y1));
				}
			}
		}

		// Store dungeon size
		DungeonSize(temp);

		// Erase top of the list
		firstToGenerate.erase(firstToGenerate.begin());
	}

	rooms.push_back(temp);
}

void RoomGen::RandomRoom()
{
	double sizeDeterminer;
	BaseRoom* temp = new BaseRoom();

	// Determine the size of the room
	do 
	{
		sizeDeterminer = GaussianRandom(0.0, 2.0);
		temp->area = (int)(multArea * sizeDeterminer);
	} while (temp->area < minArea || temp->area > maxArea); // Discard any area that is not within spec

	// We want the rooms to have an even area
	if (temp->area % 2 == 1)
	{
		temp->area -= 1;
	}

	// Calculate height and width based on the area
	if ((temp->area / minWidth) == minWidth) // Special case
	{
		temp->width = minWidth;
		temp->height = temp->area / minWidth;
	}
	else if ((temp->area / minHeight) == minHeight) // Special case
	{
		temp->height = minHeight;
		temp->width = temp->area / minHeight;
	}
	else
	{
		// Generate ratio between height/width
		bool goodRatio = false;
		while (true)
		{
			temp->width = RandomInterval(minWidth, min(maxWidth, temp->area / 2));
			temp->height = temp->area / temp->width;

			// Make sure it is good ratio
			goodRatio = false;
			if (temp->width > temp->height)
			{
				if ((double)temp->height / (double)temp->width >= maxRatio)
				{
					goodRatio = true;
				}
			} 
			else if (temp->width < temp->height)
			{
				if ((double)temp->width / (double)temp->height >= maxRatio)
				{
					goodRatio = true;
				}
			}
			else
			{
				goodRatio = true;
			}

			// Do until height is within limits and a good ratio
			if ((temp->height <= maxHeight || temp->height >= minHeight) && goodRatio == true)
			{
				break;
			}
		}
	}

	// Update with the new area
	temp->area = temp->height * temp->width;
	temp->radius = Distance2D(0.f, 0.f, temp->width / 2.f, temp->height / 2.f);
	temp->name = "Random";

	// Calculate position
	FindRoomPosition(temp);

	// Create grid data
	temp->Setup(temp->width, temp->height);

	for (unsigned int i = 0; i < temp->width; i++)
	{
		for (unsigned int j = 0; j < temp->height; j++)
		{
			temp->grid[i][j] = ROOM;
		}
	}

	// Store dungeon size
	DungeonSize(temp);

	// Add some portals to the room, depending on size
	temp->portals.push_back(new Portal(temp->x1, RandomIntervalRet(temp->y1 + 1, temp->y2 - 1)));
	temp->portals.push_back(new Portal(temp->x2, RandomIntervalRet(temp->y1 + 1, temp->y2 - 1)));
	temp->portals.push_back(new Portal(RandomIntervalRet(temp->x1 + 1, temp->x2 - 1), temp->y1));
	temp->portals.push_back(new Portal(RandomIntervalRet(temp->x1 + 1, temp->x2 - 1), temp->y2));

	// Store resulting room
	rooms.push_back(temp);
}

void RoomGen::FindRoomPosition(BaseRoom* _room, int _mode, BasePrefab* _prefab)
{
	// Mode 0 - random placement based on existing rooms
	if (_mode == 0)
	{
		// First room?
		if (rooms.size() == 0)
		{
			_room->centerX = startX;
			_room->centerY = startY;
		}
		else
		{
			// Continue until valid place is found
			while (true)
			{
				// Choose random room using Normal Distribution, we want rooms farther out
				double normalRoom = 1.0 - abs(GaussianRandom(0.0, 0.50));
				if (normalRoom < 0.0)
				{
					normalRoom = 0;
				}
				int randRoom = RandomInterval((int)(rooms.size() * normalRoom), (int)rooms.size() - 1);

				// Choose a random spot outside of that rooms radius
				float randAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (3.1415f * 2));
				int roomx = rooms[randRoom]->centerX + cos(randAngle) * (rooms[randRoom]->radius + _room->radius) * spacingX;
				int roomy = rooms[randRoom]->centerY + sin(randAngle) * (rooms[randRoom]->radius + _room->radius) * spacingY;

				// Check if the room overlaps, if it doesn't break and continue
				if (CheckRoomOverlap(_room, roomx, roomy))
				{
					break;
				}
			}
		}
	}
	// Mode 1 - spawn at a desired location, disregard any rooms there (it is up to the developer to make sure rooms doesn't overlap here)
	else if (_mode == 1)
	{
		_room->centerX = _prefab->desiredX;
		_room->centerY = _prefab->desiredY;
	}
	// Mode 2 - spawn within a radius with center at a desired location
	else if (_mode == 2)
	{
		// Continue until valid place is found
		while (true)
		{
			// Choose a random spot outside of that rooms radius
			float randAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (3.1415f * 2));
			int roomx = _prefab->desiredX + cos(randAngle) * _prefab->radius;
			int roomy = _prefab->desiredY + sin(randAngle) * _prefab->radius;

			// Check if the room overlaps, if it doesn't break and continue
			if (CheckRoomOverlap(_room, roomx, roomy))
			{
				break;
			}
		}
	}
	// Mode 3 - spawn in relation to another prefab room (order is key!)
	else if (_mode == 3)
	{
		if (_prefab->relatedRoom.compare("NONE") != 0)
		{
			int roomID = -1;
			for (unsigned int i = 0; i < rooms.size(); i++)
			{
				// Does name match?
				if (_prefab->relatedRoom.compare(rooms[i]->name) == 0)
				{
					roomID = i;
					break;
				}
			}

			// Did we find anything?
			if (roomID != -1)
			{
				// Continue until valid place is found
				while (true)
				{
					// Choose a random spot outside of that rooms radius
					float randAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (3.1415f * 2));
					int roomx = rooms[roomID]->centerX + cos(randAngle) * _prefab->radius;
					int roomy = rooms[roomID]->centerY + sin(randAngle) * _prefab->radius;

					// Check if the room overlaps, if it doesn't break and continue
					if (CheckRoomOverlap(_room, roomx, roomy))
					{
						break;
					}
				}
			}
		}
	}

	// Calculated x1, x2, y1, y2 locations
	_room->x1 = _room->centerX - _room->width / 2;
	_room->y1 = _room->centerY - _room->height / 2;
	_room->x2 = _room->x1 + _room->width;
	_room->y2 = _room->y1 + _room->height;
}

bool RoomGen::CheckRoomOverlap(BaseRoom* _room, int _x, int _y)
{
	// Make sure this place doesn't overlap another 
	for (unsigned int i = 0; i < rooms.size(); i++)
	{
		// Check radius and distance
		if (Distance2D(_x, _y, rooms[i]->centerX, rooms[i]->centerY) <= _room->radius + rooms[i]->radius)
		{
			return false;
		}
	}

	// Valid placement!
	_room->centerX = _x;
	_room->centerY = _y;

	return true;
}

void RoomGen::DungeonSize(BaseRoom* _room)
{
	// Store dungeon size
	if (_room->x1 < left)
	{
		left = _room->x1;
	}
	if (_room->x2 > right)
	{
		right = _room->x2;
	}
	if (_room->y1 < top)
	{
		top = _room->y1;
	}
	if (_room->y2 > bottom)
	{
		bottom = _room->y2;
	}
}