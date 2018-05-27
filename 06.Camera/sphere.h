#pragma once

#include "hitable.h"

class sphere : public hitable
{
public:
	sphere() {}
	sphere(vec3f cen, float r) : center(cen), radius(r) {};
	virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3f center;
	float radius;
};