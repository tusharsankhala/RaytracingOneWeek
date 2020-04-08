#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Constants.
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions.
inline double degree_to_radians(double degree)
{
	return degree * (pi / 180);
}

inline double ffmin(double a, double b)
{
	return a <= b ? a : b;
}

inline double ffmax(double a, double b)
{
	return a >= b ? a : b;
}

#endif
