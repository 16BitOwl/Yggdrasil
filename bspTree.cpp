#include "bspTree.h"
#include "dungeonGenerator.h"

BspTree::BspTree()
{
	x = y = 0;
	width = height = 0;

	parent = NULL;
	leftChild = NULL;
	rightChild = NULL;
}

BspTree::BspTree(int _x, int _y, int _width, int _height, int _minLeafSize, BspTree* _parent)
{
	minimumLeafSize = _minLeafSize;
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	parent = _parent;
	leftChild = NULL;
	rightChild = NULL;
}

BspTree::~BspTree()
{
	Clear();
}

bool BspTree::Split()
{
	// begin splitting the leaf into two children
	if (leftChild != NULL || rightChild != NULL) 
	{
		return false;
	}

	// determine direction of split
	// if the width is >25% larger than height, we split vertically
	// if the height is >25% larger than the width, we split horizontally
	// otherwise we split randomly
	float num = (rand() % 100) / 100.f;
	bool splitH = num > 0.5f;
	if (this->width > this->height && this->height / (float)this->width >= 0.05f)
	{
		splitH = false;
	} 
	else if (this->height > this->width && this->width / (float)this->height >= 0.05f)
	{
		splitH = true;
	}
	int split = (splitH ? this->height / 2 : this->width / 2); // determine the maximum height or width
	if (split <= minimumLeafSize)
	{
		return false; // the area is too small to split any more...
	}
	
	// create our left and right children based on the direction of the split
	if (splitH)
	{
		leftChild = new BspTree(this->x, this->y, this->width, split, minimumLeafSize, this);
		rightChild = new BspTree(this->x, this->y + split, this->width, this->height - split, minimumLeafSize, this);
	}
	else
	{
		leftChild = new BspTree(this->x, this->y, split, this->height, minimumLeafSize, this);
		rightChild = new BspTree(this->x + split, this->y, this->width - split, this->height, minimumLeafSize, this);
	}

	// Add rooms from parent
	if (parent != NULL)
	{
		for (unsigned int i = 0; i < parent->rooms.size(); i++)
		{
			// Check left child
			if (parent->rooms[i]->x1 < leftChild->x + leftChild->width &&
				parent->rooms[i]->x1 + parent->rooms[i]->width > leftChild->x &&
				parent->rooms[i]->y1 < leftChild->y + leftChild->height &&
				parent->rooms[i]->y1 + parent->rooms[i]->height > leftChild->y)
			{
				leftChild->rooms.push_back(parent->rooms[i]);
			}

			// Check right child
			if (parent->rooms[i]->x1 < rightChild->x + rightChild->width &&
				parent->rooms[i]->x1 + parent->rooms[i]->width > rightChild->x &&
				parent->rooms[i]->y1 < rightChild->y + rightChild->height &&
				parent->rooms[i]->y1 + parent->rooms[i]->height > rightChild->y)
			{
				rightChild->rooms.push_back(parent->rooms[i]);
			}
		}
	}

	// Continue splitting
	leftChild->Split();
	rightChild->Split();

	return true; // split successful!
}

void BspTree::Clear()
{
	// Destroy left child
	if (leftChild != NULL)
	{
		delete leftChild;
	}
	leftChild = NULL;

	// Destroy right child
	if (rightChild != NULL)
	{
		delete rightChild;
	}
	rightChild = NULL;

	// Remove rooms
	rooms.clear();
	width = height = 0;
}

void BspTree::LoadData() 
{
	CSimpleIniA iniReader;

	// Load settings file
	iniReader.SetUnicode();
	iniReader.LoadFile("dungeon.ini");

	minimumLeafSize = (int)iniReader.GetDoubleValue("BSP", "MinimumLeafSize", 10); // The minimum leaf size
}

void BspTree::Run()
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

void BspTree::PreStep()
{
	finishedStep = false;

	// Get rooms
	for (unsigned int i = 0; i < generator->roomGenerator->rooms.size(); i++)
	{
		rooms.push_back(generator->roomGenerator->rooms[i]);
	}

	width = generator->width;
	height = generator->height;
}

void BspTree::Step()
{
	Split();
	finishedStep = true;
}

void BspTree::PostStep()
{

}