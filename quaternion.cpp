#include "quaternion.h"

Quaternion::Quaternion(float w, float x, float y, float z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion::Quaternion(float angle, Vector3D& axis)
{
	const float a = angle * 0.5f;
	const float s = (float) sin(a);
	const float c = (float) cos(a);

	w = c;
	x = axis[0] * s;
	y = axis[1] * s;
	z = axis[2] * s;
}

void Quaternion::angleAxis(float& angle, Vector3D& axis) const
{
	const float squareLength = x*x + y*y + z*z;

	if (squareLength>M_EPSILONSQUARED)
	{
		angle = 2.0f * (float) acos(w);
		const float inverseLength = 1.0f / (float) pow(squareLength, 0.5f);
		axis[0] = x * inverseLength;
		axis[1] = y * inverseLength;
		axis[2] = z * inverseLength;
	}
	else
	{
		angle = 0.0f;
		axis[0] = 1.0f;
		axis[1] = 0.0f;
		axis[2] = 0.0f;
	}
}

void Quaternion::getMatrix4D(Matrix4D& iMatrix)
{
	float fTx  = 2.0f * x;
	float fTy  = 2.0f * y;
	float fTz  = 2.0f * z;
	float fTwx = fTx * w;
	float fTwy = fTy * w;
	float fTwz = fTz * w;
	float fTxx = fTx * x;
	float fTxy = fTy * x;
	float fTxz = fTz * x;
	float fTyy = fTy * y;
	float fTyz = fTz * y;
	float fTzz = fTz * z;

	iMatrix.setIdentityMatrix();

	iMatrix[0][0] = 1.0f - (fTyy + fTzz);
	iMatrix[0][1] = fTxy - fTwz;
	iMatrix[0][2] = fTxz + fTwy;

	iMatrix[1][0] = fTxy + fTwz;
	iMatrix[1][1] = 1.0f - (fTxx + fTzz);
	iMatrix[1][2] = fTyz - fTwx;

	iMatrix[2][0] = fTxz - fTwy;
	iMatrix[2][1] = fTyz + fTwx;
	iMatrix[2][2] = 1.0f - (fTxx + fTyy);
}

Matrix4D Quaternion::getMatrix4D(void)
{
	float fTx  = 2.0f * x;
	float fTy  = 2.0f * y;
	float fTz  = 2.0f * z;
	float fTwx = fTx * w;
	float fTwy = fTy * w;
	float fTwz = fTz * w;
	float fTxx = fTx * x;
	float fTxy = fTy * x;
	float fTxz = fTz * x;
	float fTyy = fTy * y;
	float fTyz = fTz * y;
	float fTzz = fTz * z;

	Matrix4D temp;
	temp.setIdentityMatrix();

	temp[0][0] = 1.0f - (fTyy + fTzz);
	temp[0][1] = fTxy - fTwz;
	temp[0][2] = fTxz + fTwy;

	temp[1][0] = fTxy + fTwz;
	temp[1][1] = 1.0f - (fTxx + fTzz);
	temp[1][2] = fTyz - fTwx;

	temp[2][0] = fTxz - fTwy;
	temp[2][1] = fTyz + fTwx;
	temp[2][2] = 1.0f - (fTxx + fTyy);

	return temp;
}

void Quaternion::zero()
{
	w = 0;
	x = 0;
	y = 0;
	z = 0;
}

void Quaternion::identity()
{
	w = 1;
	x = 0;
	y = 0;
	z = 0;
}

void Quaternion::add(const Quaternion &q)
{
	w += q.w;
	x += q.x;
	y += q.y;
	z += q.z;
}

void Quaternion::subtract(const Quaternion &q)
{
	w -= q.w;
	x -= q.x;
	y -= q.y;
	z -= q.z;
}

void Quaternion::multiply(float s)
{
	w *= s;
	x *= s;
	y *= s;
	z *= s;
}

void Quaternion::divide(float s)
{
	assert(s!=0);

	const float inv = 1.0f / s;
	w *= inv;
	x *= inv;
	y *= inv;
	z *= inv;
}

void Quaternion::multiply(const Quaternion &q)
{
	const float rw = w*q.w - x*q.x - y*q.y - z*q.z;
	const float rx = w*q.x + x*q.w + y*q.z - z*q.y;
	const float ry = w*q.y - x*q.z + y*q.w + z*q.x;
	const float rz = w*q.z + x*q.y - y*q.x + z*q.w;
	w = rw;
	x = rx;
	y = ry;
	z = rz;
}

void Quaternion::normalize()
{
	const float length = this->length();

	if (length == 0)
	{
		w = 1;
		x = 0;
		y = 0;
		z = 0;
	}
	else
	{
		float inv = 1.0f / length;
		x = x * inv;
		y = y * inv;
		z = z * inv;
		w = w * inv;
	}
}

Quaternion Quaternion::inverse() const
{
	const float n = norm();
	assert(n!=0);
	return Quaternion(w/n, -x/n, -y/n, -z/n); 
}

float& Quaternion::operator[](int i)
{
	assert(i>=0);
	assert(i<=2);
	return *(&w+i);
}

const float& Quaternion::operator[](int i) const
{
	assert(i>=0);
	assert(i<=2);
	return *(&w+i);
}

Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, float t) 
{
	assert(t>=0);
	assert(t<=1);

	float flip = 1;

	float cosine = a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z;

	if (cosine<0) 
	{ 
		cosine = -cosine; 
		flip = -1; 
	} 

	if ((1-cosine)<M_EPSILON) 
		return a * (1-t) + b * (t*flip); 

	float theta = (float)acos(cosine); 
	float sine = (float)sin(theta); 
	float beta = (float)sin((1-t)*theta) / sine; 
	float alpha = (float)sin(t*theta) / sine * flip; 

	return a * beta + b * alpha; 
} 