/*! 
* \file vector3d.h
*
* \brief Header file for the Vector3D class
*
* The entire Vector3D class is defined inside this file
*
* \author Dennis Fredriksson
* \date 2013-09-11
*/

#pragma once

#include <math.h>
#include <iostream>

using namespace std;

class Vector4D;

/*!
* \class Vector3D
*
* \brief Vector3D class, a standard implementation of a 3D vector calculations class 
*
* A Vector3D class that is used to preform various 3D vector and 3D matrix calculations
*
* \author Dennis Fredriksson
*/
class Vector3D
{
private:
	/*! 
	* \var float mValues[3]
    * \brief Contains the vector values
	* \private
	*/
	float mValues[3];

public:
	/*!
	* \brief Vector3D class constructor
	*
	* \param[float] The vector X position, defaults 0
	* \param[float] The vector Y position, defaults 0
	* \param[float] The vector Z position, defaults 0
	*/
	Vector3D(float iX = 0.f, float iY = 0.f, float iZ = 0.f);

	/*!
	* \brief Vector3D class constructor
	*
	* \param[Vector4D] The Vector4D to copy, ignores W-value
	*/
	Vector3D(Vector4D iVector);

	/*!
	* \brief Vector3D class deconstructor
	*/
	~Vector3D() {}

	/*!
	* \fn Vector3D operator=(const Vector3D iV)
	* \brief Assign the values of one Vector3D to another
	*
	* \param[const Vector3D] The second 3D vector
	* \return Vector3D
	*/
	Vector3D operator=(const Vector3D iV);

	/*!
	* \fn Vector3D operator=(const Vector4D iV)
	* \brief Assign the values of a Vector4D to a Vector3D, ignores W-value
	*
	* \param[const Vector4D] The 4D vector
	* \return Vector3D
	*/
	Vector3D operator=(const Vector4D iV);

	/*!
	* \fn Vector3D operator=(float iConst)
	* \brief Assign the value of a float to the entire vector
	*
	* \param[Vector3D] The float
	* \return Vector3D
	*/
	Vector3D operator=(float iConst);

	/*!
	* \fn float& operator[](int iConst)
	* \brief Return or change a value in the Vector
	*
	* \param[int] The value to be handled
	* \return float&
	*/
	float& operator[](int iConst);

	/*!
	* \fn const float& operator[](int iConst) const
	* \brief Return or change a value in the Vector
	*
	* \param[int] The value to be handled
	* \return float&
	*/
	const float& operator[](int iConst) const;

	/*!
	* \fn float dotProduct(Vector3D iV)
	* \brief Calculate the dot product between this vector and another 3D vector
	*
	* \param[Vector3D] The second 3D vector
	* \return float
	*/
	float dotProduct(Vector3D iV);

	/*!
	* \fn float scalarTriple(Vector3D iV1, Vector3D iV2)
	* \brief Calculate the triple scalar between this vector and two additional vectors
	*
	* \param[Vector3D] The second 3D vector
	* \param[Vector3D] The third 3D vector
	* \return float
	*/
	float scalarTriple(Vector3D iV1, Vector3D iV2);

	/*!
	* \fn void crossProduct(Vector3D iV)
	* \brief Calculate the cross product between this vector and another 3D vector
	*
	* \param[Vector3D] The second 3D vector
	*/
	void crossProduct(Vector3D iV);

	/*!
	* \fn Vector3D crossProductRet(Vector3D iV)
	* \brief Calculate the cross product between this vector and another 3D vector
	*
	* \param[Vector3D] The second 3D vector
	* \return Vector3D
	*/
	Vector3D crossProductRet(Vector3D iV);

	/*!
	* \fn float length(void)
	* \brief Calculate the length of the vector
	*
	* \return float
	*/
	float length(void);

	/*!
	* \fn void normalize(void)
	* \brief Normalize the vector
	*/
	void normalize(void);

	/*!
	* \fn void print(void)
	* \brief Debug prints the value of the vector
	*/
	void print(void);

	// Inline operator overloads

	friend inline Vector3D operator-(const Vector3D &a);
	friend inline Vector3D operator+(const Vector3D &a, const Vector3D &b);
	friend inline Vector3D operator+(const Vector3D &a, float s);
	friend inline Vector3D operator-(const Vector3D &a, const Vector3D &b);
	friend inline Vector3D operator-(const Vector3D &a, float s);
	friend inline Vector3D& operator+=(Vector3D &a, const Vector3D &b);
	friend inline Vector3D& operator-=(Vector3D &a, const Vector3D &b);

	friend inline bool operator ==(const Vector3D &q, const Vector3D &a);
	friend inline bool operator !=(const Vector3D &q, const Vector3D &a);

	friend inline Vector3D operator*(const Vector3D &a, float s);
	friend inline Vector3D operator*(float s, const Vector3D &a);
	friend inline Vector3D operator/(const Vector3D &a, float s);
	friend inline Vector3D& operator*=(Vector3D &a, float s);
	friend inline Vector3D& operator/=(Vector3D &a, float s);
};

inline Vector3D operator-(const Vector3D &a)
{
	return Vector3D(-a[0], -a[1], -a[2]);
}

inline Vector3D operator+(const Vector3D &a, const Vector3D &b)
{
	return Vector3D(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

inline Vector3D operator+(const Vector3D &a, float s)
{
	return Vector3D(a[0] + s, a[1] + s, a[2] + s);
}

inline Vector3D operator-(const Vector3D &a, const Vector3D &b)
{
	return Vector3D(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

inline Vector3D operator-(const Vector3D &a, float s)
{
	return Vector3D(a[0] - s, a[1] - s, a[2] - s);
}

inline Vector3D& operator+=(Vector3D &a, const Vector3D &b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	return a;
}

inline Vector3D& operator-=(Vector3D &a, const Vector3D &b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
	return a;
}

inline bool operator ==(const Vector3D &q, const Vector3D &a)
{
	return (q[0] == a[0] && q[1] == a[1] && q[2] == a[2]);
}

inline bool operator !=(const Vector3D &q, const Vector3D &a)
{
	return !(q == a);
}

inline Vector3D operator*(const Vector3D &a, float s)
{
	return Vector3D(a[0] * s, a[1] * s, a[2] * s);
}

inline Vector3D operator/(const Vector3D &a, float s)
{
	return Vector3D(a[0] / s, a[1] / s, a[2] / s);
}

inline Vector3D& operator*=(Vector3D &a, float s)
{
	a[0] *= s;
	a[1] *= s;
	a[2] *= s;
	return a;
}

inline Vector3D& operator/=(Vector3D &a, float s)
{
	a[0] /= s;
	a[1] /= s;
	a[2] /= s;
	return a;
}

inline Vector3D operator*(float s, const Vector3D &a)
{
	return Vector3D(a[0] * s, a[1] * s, a[2] * s);
}
