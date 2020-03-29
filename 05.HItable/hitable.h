#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"

struct hit_record
{
	float t;
	vec3f p;			// Position of hit point.
	vec3f normal;		// Normal at hit point.
};

class hitable
{
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif