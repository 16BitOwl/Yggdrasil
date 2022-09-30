/*! 
* \file matrixStack.h
*
* \brief Header file for the MatrixStack class
*
* The entire MatrixStack class is defined inside this file
*
* \author Dennis Fredriksson
* \date 2013-10-17
*/

#pragma once

#include <stack>

#include "matrix3d.h"
#include "matrix4d.h"
#include "vector3d.h"
#include "vector4d.h"

using namespace std;

struct Matrix
{
	Matrix4D mMatrix;
	Vector3D mPosition;
	Vector3D mScale;
};

/*!
* \class MatrixStack
*
* \brief MatrixStack class, a basic matrix stack
*
* The MatrixStack class is a simple, yet effective matrix stack. It functions in the same way as the built-in OpenGL matrix stack, but with special helper functions to make things a bit easier
*
* \author Dennis Fredriksson
*/
class MatrixStack
{
private:
	/*! 
	* \var stack<Matrix> mMatrixStack
    * \brief The matrix stack
	*
	* \private
	*/
	stack<Matrix> mMatrixStack;

	/*! 
	* \var Matrix mActiveMatrix
    * \brief The matrix to which all the transformations are applied to
	*
	* \private
	*/
	Matrix mActiveMatrix;

public:
	/*!
	* \brief MatrixStack class constructor
	*/
	MatrixStack();

	/*!
	* \brief MatrixStack class deconstructor
	*/
	~MatrixStack() {}

	/*!
	* \brief Multiply a translation matrix to the current stack matrix
	*
	* \param[float] The position on the X-axis
	* \param[float] The position on the Y-axis
	* \param[float] The position on the Z-axis
	*/
	void setPosition(float iPosX, float iPosY, float iPosZ);

	/*!
	* \brief Multiply a translation matrix to the current stack matrix
	*
	* \param[Vector3D] The position vector
	*/
	void setPosition(Vector3D iVector);

	/*!
	* \brief Multiply a rotation matrix to the current stack matrix
	*
	* \param[float] The rotation on the X-axis
	* \param[float] The rotation on the Y-axis
	* \param[float] The rotation on the Z-axis
	*/
	void setRotation(float iRotX, float iRotY, float iRotZ);

	/*!
	* \brief Multiply a rotation matrix to the current stack matrix
	*
	* \param[Vector3D] The rotation vector
	*/
	void setRotation(Vector3D iVector);

	/*!
	* \brief Multiply a rotation matrix to the current stack matrix
	*
	* \param[Vector3D] The rotation axis
	* \param[float] The angle
	*/
	void setAxisRotation(Vector3D iAxis, float iAngle);

	/*!
	* \brief Multiply a rotation matrix to the current stack matrix, only affects X-axis
	*
	* \param[float] The rotation on the X-axis
	*/
	void setRotationX(float iRot);

	/*!
	* \brief Multiply a rotation matrix to the current stack matrix, only affects Y-axis
	*
	* \param[float] The rotation on the Y-axis
	*/
	void setRotationY(float iRot);

	/*!
	* \brief Multiply a rotation matrix to the current stack matrix, only affects Y-axis
	*
	* \param[float] The rotation on the Y-axis
	*/
	void setRotationZ(float iRot);

	/*!
	* \brief Multiply a scale matrix to the current stack matrix
	*
	* \param[float] The scale on the X-axis
	* \param[float] The scale on the Y-axis
	* \param[float] The scale on the Z-axis
	*/
	void setScale(float iScaleX, float iScaleY, float iScaleZ);

	/*!
	* \brief Multiply a scale matrix to the current stack matrix
	*
	* \param[float] The scale on all the axis
	*/
	void setScale(float iScale);

	/*!
	* \brief Turn the current stack matrix into an identity matrix
	*/
	void setIdentity(void);

	/*!
	* \brief Multiply an external matrix to the current stack matrix
	*/
	void multMatrix(Matrix4D iMatrix);

	/*!
	* \brief Push a new matrix onto the stack. The new matrix is an exact copy of the matrix that was on top of the stack
	*/
	void pushMatrix(void);

	/*!
	* \brief Set the active matrix to the top most stack matrix and then remove the top most stack matrix
	*/
	void popMatrix(void);

	/*!
	* \brief Look at the active matrix
	*
	* \return Matrix4D&
	*/
	Matrix4D& peekMatrix(void);

	/*!
	* \brief Look at the active matrix scale log
	*
	* \return Vector3D
	*/
	Vector3D peekScaleLog(void);
};

/*! 
* \var MatrixStack gMatrixStack
* \brief The acctual matrix stack
*
* This matrix stack can be used in any class or program that includes this .h file
*
* \private
* \extern
*/
extern MatrixStack gMatrixStack;