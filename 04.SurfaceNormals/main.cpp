#include <iostream>
#include <fstream>

#include "ray.h"

#define IMG_WIDTH 600
#define IMG_HEIGHT 300


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
float hit_sphere(vec3f center, float radius, const Ray& ray)
{
	vec3f oc = ray.origin() - center;

	// Calculating the roots of the equation.
	float a = ray.direction().dot(ray.direction());
	float b = 2.0f * ray.direction().dot(oc);
	float c = oc.dot(oc) - radius * radius;

	float discriminant = b * b - (4 * a * c);

	if (discriminant < 0.0)
	{
		return -1.0;
	}
	else
	{
		return (-b - sqrtf(discriminant)) / (2.0f * a);
	}
}

// Creating the gradient texture.
vec3f color(const Ray& ray)
{
	// Getting the neatrest hit point ot no hit point at all.
	float t = hit_sphere(vec3f(0, 0, -1), 0.5f, ray);

	if (t > 0.0)
	{
		// Since t > 0.0 so there is a meaningfull root, so ray.point_at_parameter(t) will give the coordinates of
		// that root.
		vec3f N = ray.point_at_parameter(t) - vec3f(0, 0, -1);

		// Normalizing N.
		N = N.normalize();

		return vec3f(N.x() + 1, N.y() + 1, N.z() + 1) * 0.5;
	}

	vec3f ray_NormDir = ray.direction();
	ray_NormDir = ray_NormDir.normalize();

	// Since the value of y is -1 to 1, we used a common normalization trick here to remap to (0,1).
	t = 0.5f * (ray_NormDir.y() + 1.0f);

	// This basically is a lerp function.
	// Lerp : (1-t) * start + t * end; where t = Controlling Parameter.
	// t=0, color=vec3(1,1,1), multiplied by 255, the corresponding RGB is (255,255,255)  
	// t=1, color=vec3(0.5,0.7,1), multiplied by 255, corresponds to RGB (127.5,178.5,255)  
	// The above two colors correspond to "white" and "light blue" respectively.  
	// The picture color = (1-t)* "white" + t* "light blue", which is the result of the linear interpolation of the picture colors "white" and "light blue" (along the Y direction). 
	// If you want to change to X or Z direction, change the above .y() to .x() or .z().
	// To change other colors, set the corresponding RGB value.

	return (vec3f(1.0f, 1.0f, 1.0f) * (1.0f - t) + vec3f(0.5f, 0.7f, 1.0f) * t);
}

int main(int argc, char* argv[])
{

	// Creating a basic PPM image file with gradient color.
	std::ofstream imageFile;
	imageFile.open("image_SurfaceNormal.ppm");

	// Image Corner points.
	vec3f lower_left_corner(-2.0, -1.0, -1.0);
	vec3f vertical(0.0, 2.0, 0.0);
	vec3f horizontal(4.0, 0.0, 0.0);
	vec3f origin(0.0, 0.0, 0.0);

	if (imageFile)
	{
		imageFile << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n";
		imageFile << "255" << "\n";

		// Starting the image file to bottom left to top right.
		for (int y = IMG_HEIGHT - 1; y >= 0; y--)
		{
			for (int x = 0; x < IMG_WIDTH; x++)
			{
				// Normalizing the value.
				float u = float(x) / float(IMG_WIDTH);
				float v = float(y) / float(IMG_HEIGHT);

				Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
				vec3f col = color(r);

				// Again putting it in the value of 0-255.
				int iR = int(col.x() * 255.99);
				int iG = int(col.y() * 255.99);
				int iB = int(col.z() * 255.99);

				imageFile << iR << " " << iG << " " << iB << "\n";
				//std::cout << iR << " " << iG << " " << iB << "\n";
			}
		}
	}
	else
	{
		std::cout << "Error opening image file" << std::endl;
	}

	imageFile.close();

	return 0;
}