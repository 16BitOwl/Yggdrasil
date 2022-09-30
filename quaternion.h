/*! 
* \file quaternion.h
*
* \brief Header file for the Quaternion class
*
* This quaternion class is generic and may be non-unit, however most anticipated uses of quaternions are typically unit cases representing a rotation 2*acos(w) about the axis (x,y,z).
*
* \author Glenn Fiedler, altered by Dennis Fredriksson
* \date 2014-09-18
*/
#pragma once

#include "vector3d.h"
#include "miscMath.h"
#include "matrix4d.h"

#include <assert.h>

/*!
* \class Quaternion
*
* \brief Quaternion class, a standard implementation of a quaternion rotation math class
*
* A Quaternion class that is used to calculate normal rotation matrices that have no chance for gimbal locks and produce fewer numerical issues
*
* \author Glenn Fiedler, altered by Dennis Fredriksson
*/
class Quaternion
{
private:
	/*! 
	* \var float w
    * \brief Stores w component of quaternion
	* \private
	*/
	float w;

	/*! 
	* \var float x
    * \brief Stores x component of quaternion
	* \private
	*/
	float x;

	/*! 
	* \var float y
    * \brief Stores y component of quaternion
	* \private
	*/
	float y;

	/*! 
	* \var float z
    * \brief Stores z component of quaternion
	* \private
	*/
	float z;

public:
	/*!
	* \brief Quaternion class constructor
	*/
	Quaternion() {}

	/*!
	* \brief Quaternion class constructor
	*
	* \param[float] The Quaternion W value, defaults 0
	* \param[float] The Quaternion X value, defaults 0
	* \param[float] The Quaternion Y value, defaults 0
	* \param[float] The Quaternion Z value, defaults 0
	*/
	Quaternion(float w, float x, float y, float z);

	/*!
	* \brief Quaternion class constructor
	*
	* \param[float] The angle
	* \param[Vector3D&] The axis vector
	*/
	Quaternion(float angle, Vector3D& axis);

	/*!
	* \brief Converts the quaternion to angle-axis
	*
	* \param[float&] The angle
	* \param[Vector3D&] The axis vector
	*/
	void angleAxis(float& angle, Vector3D& axis) const;

	/*!
	* \brief Converts the quaternion to a 4x4 matrix
	*
	* \param[Matrix4D&] The matrix to store the quaternion in
	*/
	void getMatrix4D(Matrix4D& iMatrix);

	/*!
	* \brief Converts the quaternion to a 4x4 matrix
	*
	* \return Matrix4D
	*/
	Matrix4D getMatrix4D(void);

	/*!
	* \brief Zeros a quaternion
	*/
	void zero();

	/*!
	* \brief Sets the quaternion to identity
	*/
	void identity();

	/*!
	* \brief Add another external quaternion to this one
	*
	* \param[const Quaternion &q] The other quaternion
	*/
	void add(const Quaternion &q);

	/*!
	* \brief Subtract another external quaternion from this one
	*
	* \param[const Quaternion &q] The other quaternion
	*/
	void subtract(const Quaternion &q);

	/*!
	* \brief Multiply a scalar with this quaternion
	*
	* \param[float s] The scalar value
	*/
	void multiply(float s);

	/*!
	* \brief Divide a scalar with this quaternion
	*
	* \param[float s] The scalar value
	*/
	void divide(float s);

	/*!
	* \brief Multiply another quaternion with this quaternion
	*
	* \param[const Quaternion &q] The other quaternion
	*/
	void multiply(const Quaternion &q);

	/*!
	* \brief Calculate dot between two quaternions
	*
	* \param[const Quaternion &q] The other quaternion
	*
	* \return Quaternion
	*/
	Quaternion dot(const Quaternion &q) { return Quaternion(w*q.w + x*q.x + y*q.y + z*q.z, 0, 0, 0); }

	/*!
	* \brief Calculate conjugate of this quaternion
	*
	* \return Quaternion
	*/
	Quaternion conjugate() { return Quaternion(w, -x, -y, -z); }

	/*!
	* \brief Calculate length of quaternion
	*
	* \return float
	*/
	float length() const { return sqrt(w*w + x*x + y*y + z*z); }

	/*!
	* \brief Calculate norm of quaternion
	*
	* \return float
	*/
	float norm() const { return w*w + x*x + y*y + z*z; }

	/*!
	* \brief Normalize the quaternion
	*/
	void normalize();

	/*!
	* \brief Calculate the inverse of the quaternion
	*
	* \return Quaternion
	*/
	Quaternion inverse() const;

	/*!
	* \brief Element access to the quaternion
	*
	* Will assert of out of bounds(0< or >2)
	*
	* \param[int] Element to access
	*
	* \return float&
	*/
	float& operator[](int i);

	/*!
	* \brief Element access to the quaternion (const)
	*
	* Will assert of out of bounds(0< or >2)
	*
	* \param[int] Element to access
	*
	* \return float&
	*/
	const float& operator[](int i) const;

	/*!
	* \brief Preform a SLERP interpolation on two quaternions
	*
	* Will assert of out of bounds(0< or >2)
	*
	* \param[Quaternion&] First quaternion
	* \param[Quaternion&] Second quaternion
	* \param[float] Alpha value
	*
	* \return Quaternion
	*/
	Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);

	// Inline operator overloads

	friend inline Quaternion operator-(const Quaternion &a);
	friend inline Quaternion operator+(const Quaternion &a, const Quaternion &b);
	friend inline Quaternion operator-(const Quaternion &a, const Quaternion &b);
	friend inline Quaternion operator*(const Quaternion &a, const Quaternion &b);
	friend inline Quaternion& operator+=(Quaternion &a, const Quaternion &b);
	friend inline Quaternion& operator-=(Quaternion &a, const Quaternion &b);
	friend inline Quaternion& operator*=(Quaternion &a, const Quaternion &b);

	friend inline Quaternion operator*(const Quaternion &a, float s);
	friend inline Quaternion operator/(const Quaternion &a, float s);
	friend inline Quaternion& operator*=(Quaternion &a, float s);
	friend inline Quaternion& operator/=(Quaternion &a, float s);
	friend inline Quaternion operator*(float s, const Quaternion &a);
	friend inline Quaternion& operator*=(float s, Quaternion &a);
};


inline Quaternion operator-(const Quaternion &a)
{
	return Quaternion(-a.w, -a.x, -a.y, -a.z);
}

inline Quaternion operator+(const Quaternion &a, const Quaternion &b)
{
	return Quaternion(a.w+b.w, a.x+b.x, a.y+b.y, a.z+b.z);
}

inline Quaternion operator-(const Quaternion &a, const Quaternion &b)
{
	return Quaternion(a.w-b.w, a.x-b.x, a.y-b.y, a.z-b.z);
}

inline Quaternion operator*(const Quaternion &a, const Quaternion &b)
{
	return Quaternion( a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z, 
		a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
		a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
		a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w );
}

inline Quaternion& operator+=(Quaternion &a, const Quaternion &b)
{
	a.w += b.w;
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

inline Quaternion& operator-=(Quaternion &a, const Quaternion &b)
{
	a.w -= b.w;
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

inline Quaternion& operator*=(Quaternion &a, const Quaternion &b)
{
	a.multiply(b);
	return a;
}

inline Quaternion operator*(const Quaternion &a, float s)
{
	return Quaternion(a.w*s, a.x*s, a.y*s, a.z*s);
}

inline Quaternion operator/(const Quaternion &a, float s)
{
	return Quaternion(a.w/s, a.x/s, a.y/s, a.z/s);
}

inline Quaternion& operator*=(Quaternion &a, float s)
{
	a.multiply(s);
	return a;
}

inline Quaternion& operator/=(Quaternion &a, float s)
{
	a.divide(s);
	return a;
}

inline Quaternion operator*(float s, const Quaternion &a)
{
	return Quaternion(a.w*s, a.x*s, a.y*s, a.z*s);
}

inline Quaternion& operator*=(float s, Quaternion &a)
{
	a.multiply(s);
	return a;
}