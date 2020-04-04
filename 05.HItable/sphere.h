#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

#include "hitable.h"

class sphere : public hitable
{
public:
	sphere() : center(vec3d(0, 0, 0)), radius(1) {};
	sphere(vec3d cen, double r) : center(cen), radius(r) {};
	virtual bool hit(const Ray& r, double tmin, double tmax, hit_record& rec) const;

	vec3d center;
	double radius;
};

#endif