#include "random.h"

double RandomInterval(double _low, double _high)
{
	if (_high - _low == 0)
	{
		return 0;
	}
	return _low + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (_high - _low)));
}

int RandomInterval(int _low, int _high)
{
	if (_high - _low == 0)
	{
		return 0;
	}
	return _low + rand() % (_high - _low);
}

int RandomIntervalRet(int _low, int _high)
{
	if (_high - _low == 0)
	{
		return _high;
	}
	return _low + rand() % (_high - _low);
}

double NormalDistributionRandom()
{
	double u, v, S;

	do
	{
		// Choose a random interval between uniform [-1, 1]
		u = RandomInterval(-1.0, 1.0);
		v = RandomInterval(-1.0, 1.0);
		S = u * u + v * v;
	} while (S >= 1.0);

	// Calculate the new normal distribution random
	double fac = sqrt(-2.0 * log(S) / S);
	return u * fac;
}

double GaussianRandom(double _expectation, double _deviation)
{
	return _deviation * NormalDistributionRandom() + _expectation;
}

float Distance2D(float _x1, float _y1, float _x2, float _y2)
{
	float dx = _x1 - _x2;
	float dy = _y1 - _y2;
	return sqrt(dx * dx + dy * dy);
}