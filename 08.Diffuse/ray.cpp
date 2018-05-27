#include "ray.h"


Ray::Ray() : origin(vec3f(0.0f, 0.0f, 0.0f)), direction(vec3f(0.0f, 0.0f, 0.0f)) {}

Ray::Ray(const vec3f& or , const vec3f& dir) : origin(or ), direction(dir) {}

vec3f Ray::get_origin() const { return origin; }
vec3f Ray::get_direction() const { return direction; }

vec3f Ray::point_at_parameter(float t) const
{
	// equation: Origin + t * direction.
	return origin + t * direction;
}