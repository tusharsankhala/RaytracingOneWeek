#ifndef CAMERA_H
#define CAMERA_H

// Camera Class.

#include "ray.h"
#include "constants.h"

class Camera
{
public:
	// vFOV: Vertical FOV  top to bottom in degrees.
	Camera(vec3d lookFrom, vec3d lookAt, vec3d vup,
			double fov,
			double aspectRatio)
	{
		origin = lookFrom;
		vec3d u, v, w;

		auto theta = degree_to_radians(fov);
		auto half_height = tan(theta / 2);
		auto half_width = aspectRatio * half_height;
		w = normalize(lookFrom - lookAt);
		u = normalize(cross(vup, w));
		v = cross(w, u);

		lower_left_corner = origin - half_width * u - half_height* v - w;
		horizontal = 2 * half_width * u;
		vertical = 2 * half_height * v;
	}

	Ray get_ray(double u, double v) { return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }

public:
	vec3d origin;
	vec3d lower_left_corner;
	vec3d horizontal;
	vec3d vertical;
	
};

#endif