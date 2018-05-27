#include "camera.h"

Camera::Camera()
{
	lower_left_corner = vec3f(-2.0f, -1.0f, -1.0f);
	horizontal = vec3f(4.0f, 0.0f, 0.0f);
	vertical = vec3f(0.0f, 2.0f, 0.0f);
	origin = vec3f(0.0f, 0.0f, 0.0f);
}

Ray Camera::get_ray(float u, float v)
{
	return Ray(origin, lower_left_corner + u * horizontal + v * vertical);
}
