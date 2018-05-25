#include "ray.h"

Ray::Ray() : origin(Vec3f(0.0f, 0.0f, 0.0f)), direction(Vec3f(0.0f, 0.0f, 0.0f))
{
}

Ray::Ray(Vec3f or , Vec3f dir) : origin(or ), direction(dir)
{
}

Vec3f Ray::point_at_parameter(float t) const
{
	// equation: Origin + t * direction.
	return origin + t * direction * t;
}
