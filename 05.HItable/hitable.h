#pragma once

#include "ray.h"

// This structure records the information of the hit point.
struct hit_record
{
	float t;					// Distance t from the origin of the light.
	Vec3f p;					// Coordinate vector p of the collision point.	
	Vec3f normal;				// Normal vector at the collision point.	
};

// Abstract class hitable.
class hitable
{
public:

	// This hit() function is declared as a pure virtual function.
	// Subclasses of this class must implement their own implementation of this function. 
	virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record &rec) const = 0;
};
