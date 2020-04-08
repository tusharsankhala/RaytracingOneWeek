#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>
#include <functional>

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

inline double clamp(double val, double min, double max)
{
	if (val < min) return min;
	if (val > max) return max;

	return val;
}

inline double random_double(double min, double max)
{
	static std::uniform_real_distribution<double> distribution(min, max);
	static std::mt19937 generator;
	static std::function<double()> rand_generator = std::bind(distribution, generator);
	return rand_generator();
}

inline double random_double()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	static std::function<double()> rand_generator = std::bind(distribution, generator);
	return rand_generator();
}

#endif