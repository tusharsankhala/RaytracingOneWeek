#include "sphere.h"

//	Equation of the sphere
//	R ^ 2 = x ^ 2 + y ^ 2 + z ^ 2
//	This is a case where the center of the sphere is at (0,0,0). If we assume that the center of the sphere is C = (cx,cy,cz), then the equation becomes
//	R ^ 2 = (x-cx) ^ 2 + (y-cy) ^ 2 + (z-cz) ^ 2
//	In graphics, we can describe it as
//	R^2 = dot( p - C , p - C )
//	P is again a function of P = A + t * B, which is the ray tracing equation.
//	So you can get it
//	R^2 = dot( (A + t B - C) , (A + t B - C) )
//	Finally, R, A, B, and C are all parameters that we specify. We need to know the value of t. Just solve the equation.
//	Based on algebra knowledge, it can be introduced
//	dot(B,B) t ^ 2 + 2 dot( B , A-C ) * t + dot(A-C,A-C) - R^2 = 0

// Sphere hit test function.
// it will return the closest hit point t for the sphere.
bool sphere::hit(const Ray& ray, float t_min, float t_max, hit_record& hitrec) const
{
	vec3f oc = ray.origin() - center;

	float a = ray.direction().dot(ray.direction());
	float b = 2.0f * oc.dot(ray.direction());
	float c = oc.dot(oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrtf(discriminant)) / (2 * a);

		if (temp < t_max && temp > t_min)
		{
			hitrec.t = temp;
			hitrec.p = ray.point_at_parameter(hitrec.t);
			hitrec.normal = normalize(hitrec.p - center);			
			return true;
		}

		temp = (-b + sqrtf(discriminant)) / (2 * a);
		if (temp < t_max && temp > t_min)
		{
			hitrec.t = temp;
			hitrec.p = ray.point_at_parameter(hitrec.t);
			hitrec.normal = normalize(hitrec.p - center);
			return true;
		}
	}
	return false;
}