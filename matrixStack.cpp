#include "matrixStack.h"

MatrixStack::MatrixStack()
{
	this->mActiveMatrix.mScale = 1.f;
	this->mActiveMatrix.mPosition = 0.f;
}

void MatrixStack::setIdentity(void)
{
	this->mActiveMatrix.mMatrix.setIdentityMatrix();
}

void MatrixStack::setPosition(float iPosX, float iPosY, float iPosZ)
{
	static Matrix4D tMatrix;
	tMatrix.setPositionMatrix(iPosX, iPosY, iPosZ);

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix;

	this->mActiveMatrix.mPosition[0] += iPosX;
	this->mActiveMatrix.mPosition[1] += iPosY;
	this->mActiveMatrix.mPosition[2] += iPosZ;
}

void MatrixStack::setPosition(Vector3D iVector)
{
	static Matrix4D tMatrix;
	tMatrix.setPositionMatrix(iVector);

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix;

	this->mActiveMatrix.mPosition += iVector;
}

void MatrixStack::setRotation(float iRotX, float iRotY, float iRotZ)
{
	static Matrix4D tMatrix;
	tMatrix.setRotationMatrix(iRotX, iRotY, iRotZ);

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix;
}

void MatrixStack::setRotation(Vector3D iVector)
{
	static Matrix4D tMatrix;
	tMatrix.setRotationMatrix(iVector[0], iVector[1], iVector[2]);

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix;
}

void MatrixStack::setAxisRotation(Vector3D iAxis, float iAngle)
{
	static Matrix4D tMatrix;
	tMatrix.setRotationMatrix(iAngle, iAxis);

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix;
}

void MatrixStack::setRotationX(float iRot)
{
	static Matrix4D tMatrix;
	tMatrix.setRotationMatrix(iRot, Vector3D(1.f, 0.f, 0.f));

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix;
}

void MatrixStack::setRotationY(float iRot)
{
	static Matrix4D tMatrix;
	tMatrix.setRotationMatrix(iRot, Vector3D(0.f, 1.f, 0.f));

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix ;
}

void MatrixStack::setRotationZ(float iRot)
{
	static Matrix4D tMatrix;
	tMatrix.setRotationMatrix(iRot, Vector3D(0.f, 0.f, 1.f));

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix ;
}

void MatrixStack::setScale(float iScaleX, float iScaleY, float iScaleZ)
{
	static Matrix4D tMatrix;
	tMatrix.setScaleMatrix(iScaleX, iScaleY, iScaleZ);

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix;

	this->mActiveMatrix.mScale *= iScaleX;
}

void MatrixStack::setScale(float iScale)
{
	static Matrix4D tMatrix;
	tMatrix.setScaleMatrix(iScale);

	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * tMatrix;

	this->mActiveMatrix.mScale *= iScale;
}

void MatrixStack::multMatrix(Matrix4D iMatrix)
{
	this->mActiveMatrix.mMatrix = this->mActiveMatrix.mMatrix * iMatrix;
}

void MatrixStack::pushMatrix()
{
	this->mMatrixStack.push(this->mActiveMatrix);
}


void MatrixStack::popMatrix(void)
{
	if (this->mMatrixStack.size() > 0)
	{
		this->mActiveMatrix = this->mMatrixStack.top();
		this->mMatrixStack.pop();
	}
}

Matrix4D& MatrixStack::peekMatrix(void)
{
	return this->mActiveMatrix.mMatrix;
}

Vector3D MatrixStack::peekScaleLog(void)
{
	return this->mActiveMatrix.mScale;
}

MatrixStack gMatrixStack;