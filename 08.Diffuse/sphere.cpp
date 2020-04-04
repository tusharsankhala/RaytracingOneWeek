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
bool sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
    vec3d oc = r.origin() - center;
    auto a = r.direction().magnitude_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.magnitude_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant > 0)
    {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            vec3d outward_normal = normalize(rec.p - center);
            rec.Set_Face_Normal(r, outward_normal);
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            vec3d outward_normal = normalize(rec.p - center);
            rec.Set_Face_Normal(r, outward_normal);
            return true;
        }
    }
    return false;
}