#include "vector2d.h"

Vector2D::Vector2D(float iX, float iY)
{
	mValues[0] = iX;
	mValues[1] = iY;
}

Vector2D::~Vector2D()
{
}

Vector2D Vector2D::operator+(Vector2D iV)
{
	return Vector2D((mValues[0] + iV.mValues[0]), (mValues[1] + iV.mValues[1]));
}

Vector2D Vector2D::operator-(Vector2D iV)
{
	return Vector2D((mValues[0] - iV.mValues[0]), (mValues[1] - iV.mValues[1]));
}

Vector2D Vector2D::operator*(float iW)
{
	return Vector2D((mValues[0] * iW), (mValues[1] * iW));
}

Vector2D Vector2D::operator/(float iW)
{
	return Vector2D((mValues[0] / iW), (mValues[1] / iW));
}

Vector2D Vector2D::operator=(Vector2D iV)
{
	mValues[0] = iV.mValues[0];
	mValues[1] = iV.mValues[1];

	return *this;
}

Vector2D Vector2D::operator=(float* iConst)
{
	int tSize = sizeof(iConst) / sizeof(*iConst);

	if (tSize >= 2)
	{
		mValues[0] = iConst[0];
		mValues[1] = iConst[1];
	}
	else
	{
		throw("Error, the array must be 2 or larger to be assigned to Vector2D");
	}

	return *this;
}

bool Vector2D::operator==(Vector2D iV)
{
	if (mValues[0] != iV.mValues[0])
	{
		return false;
	}
	if (mValues[1] != iV.mValues[1])
	{
		return false;
	}

	return true;
}

float & Vector2D::operator[](int iConst)
{
	return mValues[iConst];
}

float Vector2D::length(void)
{
	return sqrt((mValues[0] * mValues[0]) + (mValues[1] * mValues[1]));
}