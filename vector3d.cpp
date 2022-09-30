#include "vector3d.h"
#include "vector4d.h"

Vector3D::Vector3D(float iX, float iY, float iZ)
{
	this->mValues[0] = iX;
	this->mValues[1] = iY;
	this->mValues[2] = iZ;
}

Vector3D::Vector3D(Vector4D iVector)
{
	this->mValues[0] = iVector[0];
	this->mValues[1] = iVector[1];
	this->mValues[2] = iVector[2];
}

Vector3D Vector3D::operator=(const Vector3D iV)
{
	this->mValues[0] = iV.mValues[0];
	this->mValues[1] = iV.mValues[1];
	this->mValues[2] = iV.mValues[2];

	return *this;
}

Vector3D Vector3D::operator=(const Vector4D iV)
{
	this->mValues[0] = iV[0];
	this->mValues[1] = iV[1];
	this->mValues[2] = iV[2];

	return *this;
}

Vector3D Vector3D::operator=(float iConst)
{
	this->mValues[0] = iConst;
	this->mValues[1] = iConst;
	this->mValues[2] = iConst;

	return *this;
}

float& Vector3D::operator[](int iConst)
{
	return this->mValues[iConst];
}

const float& Vector3D::operator[](int iConst) const
{
	return this->mValues[iConst];
}

float Vector3D::dotProduct(Vector3D iV)
{
	return (this->mValues[0] * iV.mValues[0]) + (this->mValues[1] * iV.mValues[1]) + (this->mValues[2] * iV.mValues[2]);
}

float Vector3D::scalarTriple(Vector3D iV1, Vector3D iV2)
{
	iV1.crossProduct(iV2);
	return this->dotProduct(iV1);
}

void Vector3D::crossProduct(Vector3D iV)
{
	float tX, tY, tZ;

	tX = (this->mValues[1] * iV.mValues[2]) - (this->mValues[2] * iV.mValues[1]);
	tY = (this->mValues[2] * iV.mValues[0]) - (this->mValues[0] * iV.mValues[2]);
	tZ = (this->mValues[0] * iV.mValues[1]) - (this->mValues[1] * iV.mValues[0]);

	this->mValues[0] = tX;
	this->mValues[1] = tY;
	this->mValues[2] = tZ;
}

Vector3D Vector3D::crossProductRet(Vector3D iV)
{
	float tX, tY, tZ;

	tX = (this->mValues[1] * iV.mValues[2]) - (this->mValues[2] * iV.mValues[1]);
	tY = (this->mValues[2] * iV.mValues[0]) - (this->mValues[0] * iV.mValues[2]);
	tZ = (this->mValues[0] * iV.mValues[1]) - (this->mValues[1] * iV.mValues[0]);

	return Vector3D(tX, tY, tZ);
}

float Vector3D::length(void)
{
	return sqrt(pow(this->mValues[0], 2) + pow(this->mValues[1], 2) + pow(this->mValues[2], 2));
}

void Vector3D::normalize(void)
{
	this->mValues[0] /= this->length();
	this->mValues[1] /= this->length();
	this->mValues[2] /= this->length();
}

void Vector3D::print(void)
{
	cout << "Vector3D: " << endl <<
		this->mValues[0] << ", " << this->mValues[1] << ", " << this->mValues[2] << endl;
}