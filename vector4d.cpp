#include "vector4d.h"
#include "vector3d.h"

Vector4D::Vector4D(float iX, float iY, float iZ, float iW)
{
	this->mValues[0] = iX;
	this->mValues[1] = iY;
	this->mValues[2] = iZ;
	this->mValues[3] = iW;
}

Vector4D::Vector4D(Vector3D iV, float iW)
{
	*this = iV;
	this->mValues[3] = iW;
}

Vector4D::~Vector4D()
{
}

Vector4D Vector4D::operator=(const Vector4D iV)
{
	this->mValues[0] = iV.mValues[0];
	this->mValues[1] = iV.mValues[1];
	this->mValues[2] = iV.mValues[2];
	this->mValues[3] = iV.mValues[3];

	return *this;
}

Vector4D Vector4D::operator=(const Vector3D iV)
{
	this->mValues[0] = iV[0];
	this->mValues[1] = iV[1];
	this->mValues[2] = iV[2];

	return *this;
}

Vector4D Vector4D::operator=(float iConst)
{
	this->mValues[0] = iConst;
	this->mValues[1] = iConst;
	this->mValues[2] = iConst;
	this->mValues[3] = iConst;

	return *this;
}

float& Vector4D::operator[](int iConst)
{
	return this->mValues[iConst];
}

const float& Vector4D::operator[](int iConst) const
{
	return this->mValues[iConst];
}

float Vector4D::dotProduct(Vector4D iV)
{
	return (this->mValues[0] * iV.mValues[0]) + (this->mValues[1] * iV.mValues[1]) + (this->mValues[2] * iV.mValues[2]) + (this->mValues[3] * iV.mValues[3]);
}

Vector4D& Vector4D::crossProduct(Vector4D iV1, Vector4D iV2, Vector4D iV3)
{
	float tA, tB, tC, tD, tE, tF, tX, tY, tZ, tW;

	tA = (iV2.mValues[0] * iV3.mValues[1]) - (iV2.mValues[1] * iV3.mValues[0]);
	tB = (iV2.mValues[0] * iV3.mValues[2]) - (iV2.mValues[2] * iV3.mValues[0]);
	tC = (iV2.mValues[0] * iV3.mValues[3]) - (iV2.mValues[3] * iV3.mValues[0]);
	tD = (iV2.mValues[1] * iV3.mValues[1]) - (iV2.mValues[2] * iV3.mValues[1]);
	tE = (iV2.mValues[1] * iV3.mValues[3]) - (iV2.mValues[3] * iV3.mValues[1]);
	tF = (iV2.mValues[2] * iV3.mValues[3]) - (iV2.mValues[3] * iV3.mValues[2]);

	tX = (iV1.mValues[1] * tF) - (iV1.mValues[2] * tE) + (iV1.mValues[3] * tD);
	tY = -(iV1.mValues[0] * tF) + (iV1.mValues[2] * tC) - (iV1.mValues[3] * tB);
	tZ = (iV1.mValues[0] * tE) - (iV1.mValues[1] * tC) + (iV1.mValues[3] * tA);
	tW = -(iV1.mValues[0] * tD) + (iV1.mValues[1] * tB) - (iV1.mValues[2] * tA);

	return Vector4D(tX, tY, tZ, tW);
}

void Vector4D::crossProduct(Vector4D iV)
{
	float tX, tY, tZ;

	tX = (this->mValues[1] * iV.mValues[2]) - (this->mValues[2] * iV.mValues[1]);
	tY = (this->mValues[2] * iV.mValues[0]) - (this->mValues[0] * iV.mValues[2]);
	tZ = (this->mValues[0] * iV.mValues[1]) - (this->mValues[1] * iV.mValues[0]);

	this->mValues[0] = tX;
	this->mValues[1] = tY;
	this->mValues[2] = tZ;
}

Vector4D Vector4D::crossProductRet(Vector4D iV)
{
	float tX, tY, tZ;

	tX = (this->mValues[1] * iV.mValues[2]) - (this->mValues[2] * iV.mValues[1]);
	tY = (this->mValues[2] * iV.mValues[0]) - (this->mValues[0] * iV.mValues[2]);
	tZ = (this->mValues[0] * iV.mValues[1]) - (this->mValues[1] * iV.mValues[0]);

	return Vector4D(tX, tY, tZ);
}

float Vector4D::length(void)
{
	return sqrt(pow(this->mValues[0], 2) + pow(this->mValues[1], 2) + pow(this->mValues[2], 2));
}

void Vector4D::normalize(void)
{
	this->mValues[0] /= this->length();
	this->mValues[1] /= this->length();
	this->mValues[2] /= this->length();
	this->mValues[3] /= this->length();
}

void Vector4D::print(void)
{
	cout << "Vector4D: " << endl <<
		this->mValues[0] << ", " << this->mValues[1] << ", " << this->mValues[2] << ", " << this->mValues[3] << endl;
}