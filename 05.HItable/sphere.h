#pragma once

#include "hitable.h"

// Class Sphere => Subclass of hitable.
class Sphere : public hitable
{
public:
	// Ctors.
	Sphere() {};
	Sphere(Vec3f cen, float rad) : center(cen), radius(rad) {}

	virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record &rec) const;

	Vec3f center;
	float radius;
};
