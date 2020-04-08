#ifndef MATERIAL_DIELECTRIC_H
#define MATERIAL_DIELECTRIC_H

#include "material.h"

class dielectric : public material
{
public:
	dielectric(double ri) : ref_idx(ri) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, vec3d& attenuation, Ray& scattered) const override
	{
		attenuation = vec3d(1.0, 1.0, 1.0);
		double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : ref_idx;
		
		vec3d unit_direction = normalize(r_in.direction());
		double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		if (etai_over_etat * sin_theta > 1.0)
		{
			vec3d reflected = reflect(unit_direction, rec.normal);
			scattered = Ray(rec.p, reflected);
			return true;
		}

		double reflect_prob = schlick(cos_theta, etai_over_etat);
		if (random_double() < reflect_prob)
		{
			vec3d reflected = reflect(unit_direction, rec.normal);
			scattered = Ray(rec.p, reflected);
			return true;
		}
		vec3d refracted = refract(unit_direction, rec.normal, etai_over_etat);
		scattered = Ray(rec.p, refracted);

		return true;
	}

private:
	double ref_idx;
};

#endif
