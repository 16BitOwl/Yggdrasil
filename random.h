#pragma once

#include <random>

// Random functions
int RandomInterval(int _low, int _high);
int RandomIntervalRet(int _low, int _high);
double RandomInterval(double _low, double _high);
double NormalDistributionRandom();
double GaussianRandom(double _expectation, double _deviation);

// Math functions
float Distance2D(float _x1, float _y1, float _x2, float _y2);