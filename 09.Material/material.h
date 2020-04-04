#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"

class material
{
public:
	virtual bool scatter(const Ray& r_in, const hit_record& rec, vec3d& attenuation, Ray& scattered) const = 0;
};

#endif
