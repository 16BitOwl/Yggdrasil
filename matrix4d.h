/*! 
* \file matrix4d.h
*
* \brief Header file for the Matrix4D class
*
* The entire Matrix4D class is defined inside this file
*
* \author Dennis Fredriksson
* \date 2013-09-11
*/

#pragma once

#include "vector4d.h"
#include "matrix3d.h"
#include "miscMath.h"

#include <math.h>
#include <iostream>

using namespace std;

/*!
* \class Matrix4D
*
* \brief Matrix4D class, a standard implementation of a 3D Matrix calculations class 
*
* A Matrix4D class that is used to preform various 3D Matrix calculations, such as multiplication with other 4D matrixes/vectors, addition, subtraction, tranpose and inversion
*
* \author Dennis Fredriksson
*/
class Matrix4D
{
private:
	/*! 
	* \var float mValues[4][4]
    * \brief Contains the matrix values
	* \private
	*/
	float mValues[4][4];
	
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
	* \brief Calculates a OpenGL based frustrum matrix
	*
	* \param[float] The scene bounding box left
	* \param[float] The scene bounding box right
	* \param[float] The scene bounding box top 
	* \param[float] The scene bounding box bottom
	* \param[float] The near plane 
	* \param[float] The far plane 
	* \private
	*/
	void calculateFrustrum(float iLeft, float iRight, float iTop, float iBottom, float iNear, float iFar);

	/*!
	* \brief Return the value from a given spot in the matrix
	*
	* \param[unsigned int] The matrix X value
	* \param[unsigned int] The matrix Y value
	* \return float&
	* \private
	*/
	float& getValP(unsigned int iX, unsigned int iY);

	friend class Matrix4DRow;

public:
	/*!
	* \class Matrix4DRow
	*
	* \brief Matrix4DRow class, a helper class for Matrix4D
	*
	* Matrix4DRow is used to overload the [] operator for Matrix4D
	*
	* \author Dennis Fredriksson
	*/
	class Matrix4DRow
	{
		Matrix4D& mParent;
		int mX;

	public:
		/*!
		* \brief Matrix4DRow class constructor
		*
		* \param[Matrix4D&] The 4D Matrix parent
		* \param[unsigned in] The X value 
		*/
		Matrix4DRow(Matrix4D& p, unsigned int theX) : mParent(p), mX(theX) {}

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
	* \brief Matrix4D class constructor
	*/
	Matrix4D();

	/*!
	* \brief Matrix4D class deconstructor
	*/
	~Matrix4D() {}

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
	* \brief Turn this matrix into an identity matrix
	*/
	void setIdentityMatrix();

	/*!
	* \brief Turn this matrix into a scale matrix
	*
	* \param[float] The scale on all the axis
	*/
	void setScaleMatrix(float iScale);

	/*!
	* \brief Turn this matrix into a scale matrix
	*
	* \param[float] The scale on the X-axis
	* \param[float] The scale on the Y-axis
	* \param[float] The scale on the Z-axis
	*/
	void setScaleMatrix(float iScaleX, float iScaleY, float iScaleZ);

	/*!
	* \brief Turn this matrix into a position matrix
	*
	* \param[float] The position on the X-axis
	* \param[float] The position on the Y-axis
	* \param[float] The position on the Z-axis
	*/
	void setPositionMatrix(float iPosX, float iPosY, float iPosZ);

	/*!
	* \brief Turn this matrix into a position matrix
	*
	* \param[Vector3D] The position vector
	*/
	void setPositionMatrix(Vector3D iPos);

	/*!
	* \brief Add 2 Matrix4D
	*
	* \param[Matrix4D] The second 4D matrix
	*
	* \return Matrix4D
	*/
	Matrix4D operator+(Matrix4D iMatrix);

	/*!
	* \brief Subtract 2 Matrix4D
	*
	* \param[Matrix4D] The second 4D matrix
	*
	* \return Matrix4D
	*/
	Matrix4D operator-(Matrix4D iMatrix);

	/*!
	* \brief Multiply 2 Matrix4D
	*
	* \param[Matrix4D] The second 4D matrix
	*
	* \return Matrix4D
	*/
	Matrix4D operator*(Matrix4D iMatrix);

	/*!
	* \brief Multiply a Matrix4D and a Vector4D
	*
	* \param[Vector4D] The 4D vector
	*
	* \return Vector4D
	*/
	Vector4D operator*(Vector4D iVector);

	/*!
	* \brief Scalar multiply a Matrix4D with a constant
	*
	* \param[float] The constant
	*
	* \return Matrix4D
	*/
	Matrix4D operator*(float iConst);

	/*!
	* \brief Calculate the transpose of the current Matrix4D
	*
	* \return Matrix4D
	*/
	Matrix4D operator~();

	/*!
	* \brief Compare 2 Matrix4D
	*
	* \param[Matrix4D] The second 4D matrix
	*
	* \return bool
	*/
	bool operator==(Matrix4D iMatrix);

	/*!
	* \brief Assign the values of one Matrix4D to another
	*
	* \param[Matrix4D] The second 4D matrix
	*
	* \return Matrix4D
	*/
	Matrix4D operator=(Matrix4D iMatrix);

	/*!
	* \brief Assign the values of one Matrix3D to a Matrix4D
	*
	* \param[Matrix3D] The 3D matrix
	*
	* \return Matrix4D
	*/
	Matrix4D operator=(Matrix3D iMatrix);

	/*!
	* \brief Assign the values of an array of floats to a Matrix4D
	*
	* \param[float**] The array of floats
	*
	* \return Matrix4D
	*/
	Matrix4D operator=(float** iConst);

	/*!
	* \brief Return or change a value in the Matrix
	*
	* \param[unsigned int] The X value 
	*
	* \return Matrix4DRow
	*/
	Matrix4D::Matrix4DRow operator[](unsigned int iX);

	/*!
	* \brief Inverts the matrix
	*
	* Returns true on successful invert, false on unsuccessful invert
	*
	* \return bool
	*/
	bool invert();

	/*!
	* \brief Prepares the matrix to become an orthogonal projection matrix
	*/
	void setOrthogonalProjection();

	/*!
	* \brief Prepares the matrix to become an orthogonal projection matrix
	*
	* \param[float] The scene bounding box left
	* \param[float] The scene bounding box right
	* \param[float] The scene bounding box top 
	* \param[float] The scene bounding box bottom
	* \param[float] The near plane 
	* \param[float] The far plane 
	*/
	void setOrthogonalProjection(float iLeft, float iRight, float iTop, float iBottom, float iNear, float iFar);

	/*!
	* \brief Prepares the matrix to become a perspective projection matrix
	*
	* \param[float] The near plane 
	* \param[float] The far plane 
	* \param[float] The field-of-view, in degrees 
	* \param[float] The window/screen aspect ration
	*/
	void setPerspectiveProjection(float iNear, float iFar, float iFov, float aspectRation);

	/*!
	* \brief Prepares a matrix to become a rotation matrix for the X, Y and Z axis
	*
	* \param[float] Rotation on the X-axis, in degrees
	* \param[float] Rotation on the Y-axis, in degrees
	* \param[float] Rotation on the Z-axis, in degrees
	*/
	void setRotationMatrix(float iX, float iY, float iZ);

	/*!
	* \brief Prepares a matrix to become a rotation matrix around an arbitrary axis
	*
	* \param[float] Rotation on along the axis
	* \param[Vector3D] The axis to rotate around
	*/
	void setRotationMatrix(float iAngle, Vector3D iVector);

	/*!
	* \brief Returns the matrix in a float[16] format, usable in OpenGL
	*
	* \param[float*] The float[16] array to return to
	*/
	void getFloatMatrix(float* iMatrix);
	
	/*!
	* \brief Prints the matrix to the console window
	*/
	void print(void);
};