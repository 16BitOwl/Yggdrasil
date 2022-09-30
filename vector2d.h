/*! 
* \file vector2d.h
*
* \brief Header file for the Vector2D class
*
* The entire Vector2D class is defined inside this file
*
* \author Dennis Fredriksson
* \date 2013-09-11
*/

#pragma once

#include <stdexcept>
#include <math.h>

/*!
* \class Vector2D
*
* \brief Vector2D class, a standard implementation of a 2D vector calculations class 
*
* A Vector2D class that is used to preform various 2D vector calculations
*
* \author Dennis Fredriksson
*/
class Vector2D
{
private:
	/*! 
	* \var float mValues[2]
    * \brief Contains the vector values
	*
	* \private
	*/
	float mValues[2];

public:
	/*!
	* \brief Vector2D class constructor
	*
	* \param[float] The 3D vectors X position, defaults 0
	* \param[float] The 3D vectors Y position, defaults 0
	*/
	Vector2D(float iX = 0, float iY = 0);

	/*!
	* \brief Vector2D class deconstructor
	*/
	~Vector2D();

	/*!
	* \brief Add 2 Vector2D
	*
	* \param[Vector2D] The second 2D vector
	*
	* \return Vector2D
	*/
	Vector2D operator+(Vector2D iV);

	/*!
	* \brief Subtract 2 Vector2D
	*
	* \param[Vector2D] The second 2D vector
	*
	* \return Vector2D
	*/
	Vector2D operator-(Vector2D iV);

	/*!
	* \brief Multiply a Vector2D with a constant
	*
	* \param[float] The  constant
	*
	* \return Vector2D
	*/
	Vector2D operator*(float iW);

	/*!
	* \brief Divide a Vector2D with a constant
	*
	* \param[float] The  constant
	*
	* \return Vector2D
	*/
	Vector2D operator/(float iW);

	/*!
	* \brief Assign the values of one Vector2D to another
	*
	* \param[Vector2D] The second 2D vector
	*
	* \return Vector2D
	*/
	Vector2D operator=(Vector2D iV);

	/*!
	* \brief Assign the values of a array of floats to a Vector2D
	*
	* \param[float*] The array of floats, should be atleast 3 long
	*
	* \return Vector2D
	*/
	Vector2D operator=(float* iConst);

	/*!
	* \brief Compare 2 Vector2D
	*
	* \param[Vector2D] The second 2D vector
	*
	* \return bool
	*/
	bool operator==(Vector2D iV);

	/*!
	* \brief Return or change a value in the Vector
	*
	* \param[int] The value to be handled
	*
	* \return float &
	*/
	float & operator[](int iConst);

	/*!
	* \brief Calculate the length of the vector
	*
	* \return float
	*/
	float length(void);
};