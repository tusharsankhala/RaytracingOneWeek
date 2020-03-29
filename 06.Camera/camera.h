#pragma once

// Camera Class.

#include "ray.h"

class Camera
{
public:
	Camera()
	{
		lower_left_corner = vec3f(-2.0, -1.0, -1.0);
		horizontal = vec3f(4.0, 0.0, 0.0);
		vertical = vec3f(0.0, 2.0, 0.0);
		origin = vec3f(0.0, 0.0, 0.0);
	}

	Ray get_ray(float u, float v) { return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }

	vec3f lower_left_corner;
	vec3f horizontal;
	vec3f vertical;
	vec3f origin;
};
