#include "sphere.h"

#include <cmath>

bool Sphere::hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const
{
	Vec3f oc = ray.origin - center;

	float a = ray.direction.dot(ray.direction);
	float b = 2.0f * ray.direction.dot(oc);
	float c = oc.dot(oc) - (radius * radius);

	// Calculating discreminant for the quadratic equation
	// at^2 + bt + c.

	float discreminant = b * b - 4 * a * c;

	if (discreminant > 0)
	{
		float temp = (-b - sqrtf(b * b - 4 * a * c))/2*a;

		if (temp > t_min && temp < t_max)
		{
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.normal = (rec.p - center)/radius;
			return true;
		}

		temp = (-b + sqrtf(b * b - 4 * a * c)) / 2 * a;

		if (temp > t_min && temp < t_max)
		{
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}

	return false;
}
