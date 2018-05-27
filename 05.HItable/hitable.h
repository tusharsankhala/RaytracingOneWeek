#ifndef HITABLEH
#define HITABLEH

#include "Ray.h"

struct hit_record 
{
	float t;
	vec3f p;
	vec3f normal;
};

class hitable 
{
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif