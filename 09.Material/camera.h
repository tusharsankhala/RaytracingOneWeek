#pragma once

// Camera Class.

#include "ray.h"

class Camera
{
public:
	Camera();

	Ray get_ray(float u, float v);

	vec3f lower_left_corner;
	vec3f horizontal;
	vec3f vertical;
	vec3f origin;
};
