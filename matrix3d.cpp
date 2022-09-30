#include "matrix3d.h"
#include "matrix4d.h"

Matrix3D::Matrix3D()
{
	this->mColumns = this->mRows = 3; // Make sure this is a 3x3 matrix

	for (unsigned int y = 0; y < this->mRows; y++) 
	{
		for (unsigned int x = 0; x < this->mColumns; x++) 
		{
			this->mValues[x][y] = 0;
		}
	}
}

unsigned int Matrix3D::getColumns()
{
	return this->mColumns;
}

unsigned int Matrix3D::getRows()
{
	return this->mRows;
}

float & Matrix3D::getValP(unsigned int iX, unsigned int iY)
{
	return this->mValues[iX][iY];
}

Matrix3D Matrix3D::operator+(Matrix3D iMatrix) 
{
	if (this->mColumns == iMatrix.getColumns() && this->mRows == iMatrix.getRows()) 
	{
		Matrix3D matrix;

		for (unsigned int y = 0; y < this->mRows; y++) 
		{
			for (unsigned int x = 0; x < this->mColumns; x++) 
			{
				matrix[x][y] = this->mValues[x][y] + iMatrix[x][y];
			}
		}

		return matrix;
	} 
	else 
	{
		throw("Unable to add matrices of different sizes");
	}
}

Matrix3D Matrix3D::operator-(Matrix3D iMatrix)
{
	if (this->mColumns == iMatrix.getColumns() && this->mRows == iMatrix.getRows())
	{
		Matrix3D matrix;

		for (unsigned int y = 0; y < this->mRows; y++) 
		{
			for (unsigned int x = 0; x < this->mColumns; x++) 
			{
				matrix[x][y] = this->mValues[x][y] - iMatrix[x][y];
			}
		}

		return matrix;
	} 
	else 
	{
		throw("Unable to subtract matrices of different sizes");
	}
}

Matrix3D Matrix3D::operator*(Matrix3D iMatrix)
{
	if (this->mRows == iMatrix.getColumns()) 
	{
		Matrix3D matrix;
		float value;

		for (unsigned int m = 0; m < this->mRows; m++) 
		{
			for (unsigned int y = 0; y < iMatrix.getColumns(); y++) 
			{
				value = 0;
				for (unsigned int x = 0; x < this->mColumns; x++)
				{
					value += this->mValues[x][m] * iMatrix[y][x];
				}
				matrix[y][m] = value;
			}
		}

		return matrix;
	} 
	else 
	{
		throw("Unable to multiply given matrices, incorrect sizes");
	}
}

Vector3D Matrix3D::operator*(Vector3D iVector)
{
	Vector3D vector;
	float value;

	for (unsigned int m = 0; m < this->mRows; m++) 
	{
		value = 0;
		for (unsigned int y = 0; y < this->mRows; y++) 
		{
			value += this->mValues[y][m] * iVector[y];
		}
		vector[m] = value;
	}

	return vector;
}

Matrix3D Matrix3D::operator*(float iConst) 
{
	Matrix3D matrix;

	for (unsigned int i = 0; i < this->mColumns; i++) 
	{
		for (unsigned int j = 0; j < this->mRows; j++)
		{
			matrix[i][j] = this->mValues[i][j] * iConst;
		}
	}

	return matrix;
}

Matrix3D Matrix3D::operator~() 
{
	Matrix3D matrix;

	for (unsigned int i = 0; i < this->mColumns; i++) 
	{
		for (unsigned int j = 0; j < this->mRows; j++) 
		{
			matrix[j][i] =  this->mValues[i][j];
		}
	}

	return matrix;
}

bool Matrix3D::operator==(Matrix3D iMatrix) 
{
	int counter = this->mRows * this->mColumns;

	for (unsigned int y = 0; y < this->mRows; y++) 
	{
		for (unsigned int x = 0; x < this->mColumns; x++)
		{
			if (this->mValues[x][y] == iMatrix[x][y])
			{
				counter--;
			}
		}
	}

	if (counter == 0) 
	{
		return true;
	}
	return false;
}

Matrix3D Matrix3D::operator=(Matrix3D iMatrix) 
{
	for (unsigned int y = 0; y < this->mRows; y++) 
	{
		for (unsigned int x = 0; x < this->mColumns; x++) 
		{
			this->mValues[x][y] = iMatrix[x][y];
		}
	}

	return *this;
}

Matrix3D Matrix3D::operator=(Matrix4D iMatrix)
{
	for (unsigned int y = 0; y < this->mRows; y++) 
	{
		for (unsigned int x = 0; x < this->mColumns; x++) 
		{
			this->mValues[x][y] = iMatrix[x][y];
		}
	}

	return *this;
}

Matrix3D::Matrix3DRow Matrix3D::operator[](unsigned int iX)
{
	return Matrix3DRow(*this, iX);
}

void Matrix3D::invert()
{
	// Make a copy of the current matrix for later use
	Matrix3D m = *this;

	// Calculate determinant
	float tDet = this->mValues[0][0] * (this->mValues[1][1] * this->mValues[2][2] - this->mValues[2][1] * this->mValues[1][2]) -
				 this->mValues[0][1] * (this->mValues[1][0] * this->mValues[2][2] - this->mValues[1][2] * this->mValues[2][0]) +
				 this->mValues[0][2] * (this->mValues[1][0] * this->mValues[2][1] - this->mValues[1][1] * this->mValues[2][0]);
	float tInvDet = 1 / tDet;

	// Calculate the inverse of the 3D matrix
	this->mValues[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * tInvDet;
	this->mValues[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * tInvDet;
	this->mValues[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * tInvDet;
	this->mValues[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * tInvDet;
	this->mValues[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * tInvDet;
	this->mValues[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * tInvDet;
	this->mValues[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * tInvDet;
	this->mValues[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * tInvDet;
	this->mValues[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * tInvDet;
}

void Matrix3D::getFloatMatrix(float* iMatrix)
{
	for (int i = 0; i < 9; i++)
	{
		iMatrix[i] = this->mValues[i/3][i%3];
	}
}

void Matrix3D::print(void)
{
	cout << "Matrix3D: " << endl << 
		this->mValues[0][0] << ", " << this->mValues[0][1] << ", " << this->mValues[0][2] << endl << 
		this->mValues[1][0] << ", " << this->mValues[1][1] << ", " << this->mValues[1][2] << endl << 
		this->mValues[2][0] << ", " << this->mValues[2][1] << ", " << this->mValues[2][2] << endl;
}