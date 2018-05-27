#include "sphere.h"

bool sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const 
{
	vec3f oc = r.origin - center;

	float a = r.get_direction().dot(r.get_direction());
	float b = oc.dot(r.get_direction());
	float c = oc.dot(oc) - radius*radius;
	float discriminant = b*b - a*c;
	if (discriminant > 0) 
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) 
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) 
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}