/*! 
* \file vector4d.h
*
* \brief Header file for the Vector4D class
*
* The entire Vector4D class is defined inside this file
*
* \author Dennis Fredriksson
* \date 2013-09-21
*/

#pragma once

#include <iostream>
#include <math.h>

using namespace std;

class Vector3D;

/*!
* \class Vector4D
*
* \brief Vector4D class, a standard implementation of a 4D vector calculations class 
*
* A Vector4D class that is used to preform various 4D vector and 4D matrix calculations
*
* \author Dennis Fredriksson
*/
class Vector4D
{
private:
	/*! 
	* \var float mValues[4]
    * \brief Contains the vector values
	* \private
	*/
	float mValues[4];

public:
	/*!
	* \brief Vector4D class constructor
	*
	* \param[float] The vector X position, defaults 0.f
	* \param[float] The vector Y position, defaults 0.f
	* \param[float] The vector Z position, defaults 0.f
	* \param[float] The vector W position, defaults 0.f
	*/
	Vector4D(float iX = 0.f, float iY = 0.f, float iZ = 0.f, float iW = 0.f);

	/*!
	* \brief Vector4D class constructor
	*
	* \param[Vector3D] The 3D vector to copy
	* \param[float] The 4D vectors W position, defaults 0.f
	*/
	Vector4D(Vector3D iV, float iW = 0.f);

	/*!
	* \brief Vector3D class deconstructor
	*/
	~Vector4D();

	/*!
	* \brief Assign the values of one Vector4D to another
	*
	* \param[const Vector4D] The second 4D vector
	* \return Vector4D&
	*/
	Vector4D operator=(const Vector4D iV);

	/*!
	* \brief Assign the values of one Vector3D to a Vector4D
	*
	* \param[const Vector4D] The second 3D vector
	* \return Vector4D&
	*/
	Vector4D operator=(const Vector3D iV);

	/*!
	* \brief Assign the value of a single float to the vector
	*
	* \param[float] The float
	* \return Vector4D&
	*/
	Vector4D operator=(float iConst);

	/*!
	* \brief Return or change a value in the Vector
	*
	* \param[int] The value to be handled
	* \return float&
	*/
	float& operator[](int iConst);

	/*!
	* \brief Return or change a value in the Vector
	*
	* \param[int] The value to be handled
	* \return float&
	*/
	const float& operator[](int iConst) const;

	/*!
	* \brief Calculate the dot product between this vector and another 4D vector
	*
	* \param[Vector4D] The second 4D vector
	* \return float
	*/
	float dotProduct(Vector4D iV);

	/*!
	* \brief Calculate the cross product between three different vectors, returns a Vector4D
	*
	* \param[Vector4D] The first 4D vector
	* \param[Vector4D] The second 4D vector
	* \param[Vector4D] The third 4D vector
	* \return Vector4D&
	*/
	Vector4D& Vector4D::crossProduct(Vector4D iV1, Vector4D iV2, Vector4D iV3);

	/*!
	* \brief Calculate the cross product between this vector and another 4D vector. Will ignore W value of vector
	*
	* \param[Vector4D] The second 4D vector
	*/
	void crossProduct(Vector4D iV);

	/*!
	* \brief Calculate the cross product between this vector and another 4D vector. Will ignore W value of vector
	*
	* \param[Vector4D] The second 4D vector
	* \return Vector4D
	*/
	Vector4D crossProductRet(Vector4D iV);

	/*!
	* \brief Calculate the length of the vector
	*
	* \return float
	*/
	float length(void);

	/*!
	* \brief Normalize the vector
	*/
	void normalize(void);

	/*!
	* \brief Debug prints the value of the vector
	*/
	void print(void);

	// Inline operator overloads

	friend inline Vector4D operator-(const Vector4D &a);
	friend inline Vector4D operator+(const Vector4D &a, const Vector4D &b);
	friend inline Vector4D operator+(const Vector4D &a, float s);
	friend inline Vector4D operator-(const Vector4D &a, const Vector4D &b);
	friend inline Vector4D operator-(const Vector4D &a, float s);
	friend inline Vector4D& operator+=(Vector4D &a, const Vector4D &b);
	friend inline Vector4D& operator-=(Vector4D &a, const Vector4D &b);

	friend inline bool operator ==(const Vector4D &q, const Vector4D &a);
	friend inline bool operator !=(const Vector4D &q, const Vector4D &a);

	friend inline Vector4D operator*(const Vector4D &a, float s);
	friend inline Vector4D operator*(float s, const Vector4D &a);
	friend inline Vector4D operator/(const Vector4D &a, float s);
	friend inline Vector4D& operator*=(Vector4D &a, float s);
	friend inline Vector4D& operator/=(Vector4D &a, float s);
};

inline Vector4D operator-(const Vector4D &a)
{
	return Vector4D(-a[0], -a[1], -a[2], -a[3]);
}

inline Vector4D operator+(const Vector4D &a, const Vector4D &b)
{
	return Vector4D(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
}

inline Vector4D operator+(const Vector4D &a, float s)
{
	return Vector4D(a[0] + s, a[1] + s, a[2] + s, a[3] + s);
}

inline Vector4D operator-(const Vector4D &a, const Vector4D &b)
{
	return Vector4D(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
}

inline Vector4D operator-(const Vector4D &a, float s)
{
	return Vector4D(a[0] - s, a[1] - s, a[2] - s, a[3] - s);
}

inline Vector4D& operator+=(Vector4D &a, const Vector4D &b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	a[3] += b[3];
	return a;
}

inline Vector4D& operator-=(Vector4D &a, const Vector4D &b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
	a[3] -= b[3];
	return a;
}

inline bool operator ==(const Vector4D &q, const Vector4D &a)
{
	return (q[0] == a[0] && q[1] == a[1] && q[2] == a[2] && q[3] == a[3]);
}

inline bool operator !=(const Vector4D &q, const Vector4D &a)
{
	return !(q == a);
}

inline Vector4D operator*(const Vector4D &a, float s)
{
	return Vector4D(a[0] * s, a[1] * s, a[2] * s, a[3] * s);
}

inline Vector4D operator/(const Vector4D &a, float s)
{
	return Vector4D(a[0] / s, a[1] / s, a[2] / s, a[3] / s);
}

inline Vector4D& operator*=(Vector4D &a, float s)
{
	a[0] *= s;
	a[1] *= s;
	a[2] *= s;
	a[3] *= s;
	return a;
}

inline Vector4D& operator/=(Vector4D &a, float s)
{
	a[0] /= s;
	a[1] /= s;
	a[2] /= s;
	a[3] /= s;
	return a;
}

inline Vector4D operator*(float s, const Vector4D &a)
{
	return Vector4D(a[0] * s, a[1] * s, a[2] * s, a[3] * s);
}
