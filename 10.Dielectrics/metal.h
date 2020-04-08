#ifndef METAL_H
#define METAL_H

#include "material.h"

class metal : public material
{
public:
	metal(const vec3d& a, const double fuzz) : albedo(a), fuzziness(fuzz < 1 ? fuzz : 1) {}

	bool scatter(const Ray& r_in, const hit_record& rec, vec3d& attenuation, Ray& scattered) const override
	{
		vec3d reflected = reflect(normalize(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzziness * vec3d::random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

private:
	vec3d albedo;
	double fuzziness;
};

#endif