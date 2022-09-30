#include "matrix4d.h"

Matrix4D::Matrix4D()
{
	this->mColumns = this->mRows = 4; // Make sure this is a 4x4 matrix

	for (unsigned int y = 0; y < this->mRows; y++) 
	{
		for (unsigned int x = 0; x < this->mColumns; x++) 
		{
			this->mValues[x][y] = 0.f;
		}
	}
}

float & Matrix4D::getValP(unsigned int iX, unsigned int iY)
{
	return this->mValues[iX][iY];
}

unsigned int Matrix4D::getColumns()
{
	return this->mColumns;
}

unsigned int Matrix4D::getRows()
{
	return this->mRows;
}

void Matrix4D::setIdentityMatrix()
{
	this->mValues[0][0] = 1.f;
	this->mValues[1][1] = 1.f;
	this->mValues[2][2] = 1.f;
	this->mValues[3][3] = 1.f;
}

void Matrix4D::setScaleMatrix(float iScaleX, float iScaleY, float iScaleZ)
{
	this->mValues[0][0] = iScaleX;
	this->mValues[1][1] = iScaleY;
	this->mValues[2][2] = iScaleZ;
	this->mValues[3][3] = 1.f;
}

void Matrix4D::setScaleMatrix(float iScale)
{
	this->mValues[0][0] = iScale;
	this->mValues[1][1] = iScale;
	this->mValues[2][2] = iScale;
	this->mValues[3][3] = 1.f;
}

void Matrix4D::setPositionMatrix(float iPosX, float iPosY, float iPosZ)
{
	this->setIdentityMatrix();

	this->mValues[3][0] = iPosX;
	this->mValues[3][1] = iPosY;
	this->mValues[3][2] = iPosZ;
}

void Matrix4D::setPositionMatrix(Vector3D iPos)
{
	this->setIdentityMatrix();

	this->mValues[3][0] = iPos[0];
	this->mValues[3][1] = iPos[1];
	this->mValues[3][2] = iPos[2];
}

Matrix4D Matrix4D::operator+(Matrix4D iMatrix) 
{
	if (this->mColumns == iMatrix.getColumns() && this->mRows == iMatrix.getRows()) 
	{
		Matrix4D matrix;

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

Matrix4D Matrix4D::operator-(Matrix4D iMatrix)
{
	if (this->mColumns == iMatrix.getColumns() && this->mRows == iMatrix.getRows())
	{
		Matrix4D matrix;

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

Matrix4D Matrix4D::operator*(Matrix4D iMatrix)
{
	if (this->mRows == iMatrix.getColumns()) 
	{
		Matrix4D matrix;
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

Vector4D Matrix4D::operator*(Vector4D iVector)
{
	Vector4D vector;
	float val;

	for (unsigned int m = 0; m < this->mRows; m++) 
	{
		val = 0;
		for (unsigned int y = 0; y < this->mColumns; y++) 
		{
			val += this->mValues[y][m] * iVector[y];
		}
		vector[m] = val;
	}

	return vector;
}

Matrix4D Matrix4D::operator*(float iConst) 
{
	Matrix4D matrix;

	for (unsigned int i = 0; i < this->mColumns; i++) 
	{
		for (unsigned int j = 0; j < this->mRows; j++)
		{
			matrix[i][j] = this->mValues[i][j] * iConst;
		}
	}

	return matrix;
}

Matrix4D Matrix4D::operator~() 
{
	Matrix4D matrix;

	for (unsigned int i = 0; i < this->mColumns; i++) 
	{
		for (unsigned int j = 0; j < this->mRows; j++) 
		{
			matrix[j][i] = this->mValues[i][j];
		}
	}

	return matrix;
}

bool Matrix4D::operator==(Matrix4D iMatrix) 
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

Matrix4D Matrix4D::operator=(Matrix4D iMatrix) 
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

Matrix4D Matrix4D::operator=(Matrix3D iMatrix) 
{

	for (unsigned int y = 0; y < iMatrix.getRows(); y++) 
	{
		for (unsigned int x = 0; x < iMatrix.getColumns(); x++) 
		{
			this->mValues[x][y] = iMatrix[x][y];
		}
	}

	return *this;
}

Matrix4D Matrix4D::operator=(float** iConst) 
{
	if (this->mRows != sizeof(iConst) / sizeof(iConst[0][0]) || this->mColumns != sizeof(*iConst) / sizeof(iConst[0][0])) 
	{
		throw("Matrices of different sizes cannot be copied/equaled, unless resized");
	}

	for (unsigned int y = 0; y < this->mRows; y++) 
	{
		for (unsigned int x = 0; x < this->mColumns; x++) 
		{
			this->mValues[x][y] = iConst[x][y];
		}
	}

	return *this;
}

Matrix4D::Matrix4DRow Matrix4D::operator[](unsigned int iX)
{
	return Matrix4DRow(*this, iX);
}

bool Matrix4D::invert()
{
	float inv[16], m[16], det;
    int i;

	for (i = 0; i < 16; i++)
	{
		m[i] = this->mValues[i/4][i%4];
	}

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
	{
        return false;
	}

    det = 1.0f / det;

    for (i = 0; i < 16; i++)
	{
        this->mValues[i/4][i%4] = inv[i] * det;
	}

    return true;
}

void Matrix4D::setOrthogonalProjection()
{
	this->mValues[0][0] = 1;
	this->mValues[1][1] = 1;
	this->mValues[3][3] = 1;
}

void Matrix4D::setOrthogonalProjection(float iLeft, float iRight, float iTop, float iBottom, float iNear, float iFar)
{
	this->mValues[0][0] = 2 / (iRight - iLeft);
    this->mValues[0][1] = 0;
    this->mValues[0][2] = 0;
    this->mValues[0][3] = 0;
 
    this->mValues[1][0] = 0;
    this->mValues[1][1] = 2 / (iTop - iBottom);
    this->mValues[1][2] = 0;
    this->mValues[1][3] = 0;
 
    this->mValues[2][0] = 0;
    this->mValues[2][1] = 0;
    this->mValues[2][2] = -1 / (iTop - iNear);
    this->mValues[2][3] = 0;
 
    this->mValues[3][0] = -(iRight + iLeft) / (iRight - iLeft);
    this->mValues[3][1] = -(iTop + iBottom) / (iTop - iBottom);
    this->mValues[3][2] = -iNear / (iFar - iNear);
    this->mValues[3][3] = 1;
}

void Matrix4D::setPerspectiveProjection(float iNear, float iFar, float iFov, float iAspectRation)
{
	float tScale = tan((iFov * 0.5f) * (M_PI / 180)) * iNear;
    float tR = iAspectRation * tScale, tL = -tR;
    float tT = tScale, tB = -tT;

	calculateFrustrum(tL, tR, tB, tT, iNear, iFar);
}

void Matrix4D::calculateFrustrum(float iLeft, float iRight, float iTop, float iBottom, float iNear, float iFar)
{
	this->mValues[0][0] = 2.f * iNear / (iRight - iLeft);
    this->mValues[0][1] = 0.f;
    this->mValues[0][2] = 0.f;
    this->mValues[0][3] = 0.f;
 
    this->mValues[1][0] = 0.f;
    this->mValues[1][1] = -2.f * iNear / (iTop - iBottom);
    this->mValues[1][2] = 0.f;
    this->mValues[1][3] = 0.f;
 
    this->mValues[2][0] = (iRight + iLeft) / (iRight - iLeft);
    this->mValues[2][1] = (iTop + iBottom) / (iTop - iBottom);
    this->mValues[2][2] = -(iFar + iNear) / (iFar - iNear);
    this->mValues[2][3] = -1.f;
 
    this->mValues[3][0] = 0.f;
    this->mValues[3][1] = 0.f;
    this->mValues[3][2] = -2.f * iFar * iNear / (iFar - iNear);
    this->mValues[3][3] = 0.f;
}

void Matrix4D::setRotationMatrix(float iX, float iY, float iZ)
{
	Matrix4D tMatrixX, tMatrixY, tMatrixZ, tMatrix;
	float iXR = iX * (M_PI / 180), iYR = iY * (M_PI / 180), iZR = iZ * (M_PI / 180); 

	// Set the values in the first rotation matrix, X
	tMatrixX[0][0] = 1.f;
	tMatrixX[3][3] = 1.f;
	tMatrixX[1][1] = cos(iXR);
	tMatrixX[1][2] = sin(iXR);
	tMatrixX[2][1] = -sin(iXR);
	tMatrixX[2][2] = cos(iXR);

	// Set the values in the second rotation matrix, Y
	tMatrixY[1][1] = 1.f;
	tMatrixY[3][3] = 1.f;
	tMatrixY[0][0] = cos(iYR);
	tMatrixY[0][2] = -sin(iYR);
	tMatrixY[2][0] = sin(iYR);
	tMatrixY[2][2] = cos(iYR);

	// Set the values in the third rotation matrix, Z
	tMatrixZ[2][2] = 1.f;
	tMatrixZ[3][3] = 1.f;
	tMatrixZ[0][0] = cos(iZR);
	tMatrixZ[0][1] = sin(iZR);
	tMatrixZ[1][0] = -sin(iZR);
	tMatrixZ[1][1] = cos(iZR);

	// Calculate the final rotation matrix
	*this = tMatrixX * tMatrixY * tMatrixZ;
}

void Matrix4D::setRotationMatrix(float iAngle, Vector3D iVector)
{
	float iAngleR = iAngle * (M_PI / 180);
	float tX = iVector[0], tY = iVector[1], tZ = iVector[2];
	float tC = cos(iAngleR), tS = sin(iAngleR), tT = 1 - cos(iAngleR);

	// Setup the rotation matrix
	this->mValues[3][3] = 1.f;

	this->mValues[0][0] = tT * pow(tX, 2) + tC;
	this->mValues[0][1] = tT * tX * tY + tS * tZ;
	this->mValues[0][2] = tT * tX * tZ - tS * tY;

	this->mValues[1][0] = tT * tX * tY - tS * tZ;
	this->mValues[1][1] = tT * pow(tY, 2) + tC;
	this->mValues[1][2] = tT * tY * tZ + tS * tX;

	this->mValues[2][0] = tT * tX * tZ + tS * tY;
	this->mValues[2][1] = tT * tY * tZ - tS * tX;
	this->mValues[2][2] = tT * pow(tZ, 2) + tC;
}

void Matrix4D::getFloatMatrix(float* iMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		iMatrix[i] = this->mValues[i/4][i%4];
	}
}

void Matrix4D::print(void)
{
	cout << "Matrix4D: " << endl << 
		this->mValues[0][0] << ", " << this->mValues[0][1] << ", " << this->mValues[0][2] << ", " << this->mValues[0][3] << endl << 
		this->mValues[1][0] << ", " << this->mValues[1][1] << ", " << this->mValues[1][2] << ", " << this->mValues[1][3] << endl << 
		this->mValues[2][0] << ", " << this->mValues[2][1] << ", " << this->mValues[2][2] << ", " << this->mValues[2][3] << endl << 
		this->mValues[3][0] << ", " << this->mValues[3][1] << ", " << this->mValues[3][2] << ", " << this->mValues[3][3] << endl; 
}