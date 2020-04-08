#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class lambertian : public material
{
public:
	lambertian(const vec3d& a) : albedo(a) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, vec3d& attenuation, Ray& scattered) const override
	{
		vec3d scatter_direction = rec.normal + vec3d::random_in_unit_sphere();
		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

private:
	vec3d albedo;
};

#endif
