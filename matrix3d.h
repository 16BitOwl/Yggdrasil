/*! 
* \file matrix3d.h
*
* \brief Header file for the Matrix3D class
*
* The entire Matrix3D class is defined inside this file
*
* \author Dennis Fredriksson
* \date 2013-09-11
*/

#pragma once

#include "vector3d.h"

#include <math.h>
#include <iostream>

class Matrix4D;

using namespace std;

/*!
* \class Matrix3D
*
* \brief Matrix3D class, a standard implementation of a 3D Matrix calculations class 
*
* A Matrix3D class that is used to preform various 3D Matrix calculations, such as multiplication with other 3D matrixes/vectors, addition, subtraction, tranpose and inversion
*
* \author Dennis Fredriksson
*/
class Matrix3D
{
private:
	/*! 
	* \var float mValues[3][3]
    * \brief Contains the matrix values
	* \private
	*/
	float mValues[3][3];

	/*! 
	* \var unsigned int mColumns
    * \brief Contains the matrix column size
	* \private
	*/
	unsigned int mColumns;

	/*! 
	* \var unsigned int mRows
    * \brief Contains the matrix row size
	* \private
	*/
	unsigned int mRows;

	/*!
	* \brief Return the value from a given spot in the matrix
	*
	* \param[unsigned int] The matrix X value
	* \param[unsigned int] The matrix Y value
	* \return float&
	* \private
	*/
	float& getValP(unsigned int iX, unsigned int iY);

	friend class Matrix3DRow;

public:
	/*!
	* \class Matrix3DRow
	*
	* \brief Matrix3DRow class, a helper class for Matrix3D
	*
	* Matrix3DRow is used to overload the [] operator for Matrix3D
	*
	* \author Dennis Fredriksson
	*/
	class Matrix3DRow
	{
		Matrix3D& mParent;
		int mX;

	public:
		/*!
		* \brief Matrix3DRow class constructor
		*
		* \param[Matrix3D&] The 3D Matrix parent
		* \param[unsigned in] The X value 
		*/
		Matrix3DRow(Matrix3D& p, unsigned int theX) : mParent(p), mX(theX) {}

		/*!
		* \brief Return or change a value in the Matrix
		*
		* \param[unsigned int] The Y value 
		*
		* \return float &
		*/
		float & operator[](unsigned int iY) const { return mParent.getValP(mX, iY); }
	};

	/*!
	* \brief Matrix3D class constructor
	*/
	Matrix3D();

	/*!
	* \brief Matrix3D class deconstructor
	*/
	~Matrix3D() {}

	/*!
	* \brief Return the amount of columns
	*
	* \return unsigned int
	*/
	unsigned int getColumns();

	/*!
	* \brief Return the amount of rows
	*
	* \return unsigned int
	*/
	unsigned int getRows();

	/*!
	* \brief Add 2 Matrix3D
	*
	* \param[Matrix3D] The second 3D matrix
	*
	* \return Matrix3D
	*/
	Matrix3D operator+(Matrix3D iMatrix);

	/*!
	* \brief Subtract 2 Matrix3D
	*
	* \param[Matrix3D] The second 3D matrix
	*
	* \return Matrix3D
	*/
	Matrix3D operator-(Matrix3D iMatrix);

	/*!
	* \brief Multiply 2 Matrix3D
	*
	* \param[Matrix3D] The second 3D matrix
	*
	* \return Matrix3D
	*/
	Matrix3D operator*(Matrix3D iMatrix);

	/*!
	* \brief Multiply a Matrix3D and a Vector3D
	*
	* \param[Matrix3D] The second 3D matrix
	*
	* \return Matrix3D
	*/
	Vector3D operator*(Vector3D iVector);

	/*!
	* \brief Scalar multiply a Matrix3D with a constant
	*
	* \param[float] The constant
	*
	* \return Matrix3D
	*/
	Matrix3D operator*(float iConst);

	/*!
	* \brief Calculate the transpose of the current Matrix3D
	*
	* \return Matrix3D
	*/
	Matrix3D operator~();

	/*!
	* \brief Compare 2 Matrix3D
	*
	* \param[Matrix3D] The second 3D matrix
	* \return bool
	*/
	bool operator==(Matrix3D iMatrix);

	/*!
	* \brief Assign the values of one Matrix3D to another
	*
	* \param[Matrix3D] The second 3D matrix
	* \return Matrix3D
	*/
	Matrix3D operator=(Matrix3D iMatrix);

	/*!
	* \brief Assign the values of the sub-matrix of a Matrix4D
	*
	* \param[Matrix4D] The 4D matrix
	* \return Matrix3D
	*/
	Matrix3D operator=(Matrix4D iMatrix);

	/*!
	* \brief Return or change a value in the Matrix
	*
	* \param[unsigned int] The X value 
	*
	* \return Matrix3DRow
	*/
	Matrix3D::Matrix3DRow operator[](unsigned int iX);

	/*!
	* \brief Inverts the matrix
	*/
	void invert();

	/*!
	* \brief Returns the matrix in a float[9] format, usable in OpenGL
	*
	* \param[float*] The float[9] array to return to
	*/
	void getFloatMatrix(float* iMatrix);

	/*!
	* \brief Prints the matrix to the console window
	*/
	void print(void);
};