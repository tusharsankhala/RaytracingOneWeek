#pragma once

// Camera Class.

#include "ray.h"
#include "constants.h"

class Camera
{
public:
	Camera()
	{
		lower_left_corner = vec3d(-2.0, -1.0, -1.0);
		horizontal = vec3d(4.0, 0.0, 0.0);
		vertical = vec3d(0.0, 2.0, 0.0);
		origin = vec3d(0.0, 0.0, 0.0);
	}

	Ray get_ray(double u, double v) { return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }

	vec3d lower_left_corner;
	vec3d horizontal;
	vec3d vertical;
	vec3d origin;
};
