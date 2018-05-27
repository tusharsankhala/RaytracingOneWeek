#include "ray.h"


Ray::Ray() : origin(vec3(0.0f, 0.0f, 0.0f)), direction(vec3(0.0f, 0.0f, 0.0f)) {}

Ray::Ray(const vec3& or , const vec3& dir) : origin(or), direction(dir) {}

vec3 Ray::point_at_parameter(float t) const
{
	// equation: Origin + t * direction.
	return origin + t * direction;
}