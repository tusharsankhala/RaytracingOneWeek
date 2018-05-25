#pragma once

#include "vec3.h"

class Ray
{
public:
	// Ctor.

	// Default Constructor.
	Ray();

	// Copy Constructor.
	Ray(Vec3f or , Vec3f dir);

	// Calculating Point at parameter (t).
	// equation: Origin + t * direction.
	Vec3f point_at_parameter(float t) const;

	// Ray Origin and Distance.
	Vec3f origin;
	Vec3f direction;
};