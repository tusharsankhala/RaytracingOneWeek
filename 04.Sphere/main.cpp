#include <iostream>
#include <fstream>

#include "ray.h"

#define IMG_WIDTH 400
#define IMG_HEIGHT 200


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
bool hit_sphere(const vec3d center, const double radius, const Ray& ray)
{
	vec3d oc = center - ray.origin();

	// Calculating roots of the equation.
	auto a = dot(ray.direction(), ray.direction());
	float b = 2 * dot(oc, ray.direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b - 4 * a * c;

	return (discriminant > 0);
}


// Creating the gradient texture.
vec3d color(const Ray& ray)
{
	if (hit_sphere(vec3d(0.0, 0.0, -1.0), 0.5, ray))
		return vec3d(1.0, 0.0, 0.0);

	vec3d unitDirection = ray.direction().normalize();
	
	// normaldirection has range from [-1, 1] so bringing
	// it into the range ofo [0,1].
	double t = 0.5 * (unitDirection.y() + 1.0);

	// This basically is a lerp function.
	// Lerp : (1-t) * start + t * end; where t = Controlling Parameter.
	// t=0, color=vec3(1,1,1), multiplied by 255, the corresponding RGB is (255,255,255) = white color.  
	// t=1, color=vec3(0.5,0.7,1), multiplied by 255, corresponds to RGB (127.5,178.5,255) = sky blue color.  
	// The above two colors correspond to "white" and "light blue" respectively.  
	// The picture color = (1-t) * white + t * light blue, which is the result of the linear interpolation of the picture colors
	// "white" and "light blue" (along the Y direction). 
	return (1 - t) * vec3d(1.0, 1.0, 1.0) + t * vec3d(0.5, 0.7, 1.0);
}


int main(int argc, char* argv[])
{
	std::ofstream imageFile;
	try
	{
		imageFile.open("Output_04Sphere.ppm");
		if (imageFile)
		{
			imageFile << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n255\n";

			vec3d lower_left_corner(-2.0, -1.0, -1.0);
			vec3d horizontal(4.0, 0.0, 0.0);
			vec3d vertical(0.0, 2.0, 0.0);
			vec3d origin(0.0, 0.0, 0.0);

			// Y (Top to Bottom)
			// X (Left to right)
			for (int y = IMG_HEIGHT - 1; y >= 0; --y)
			{
				std::cerr << "\rScanline Rendering Remaining: " << y << ' ' << std::flush;
				for (int x = 0; x < IMG_WIDTH; ++x)
				{
					auto u = double(x) / IMG_WIDTH;
					auto v = double(y) / IMG_HEIGHT;

					Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
					vec3d col = color(ray);
					int r = static_cast<int>(255.99 * col[0]);
					int g = static_cast<int>(255.99 * col[1]);
					int b = static_cast<int>(255.99 * col[2]);

					imageFile << r << " " << g << " " << b << "\n";
				}
			}
		}
	}
	catch (std::exception ex)
	{
		std::cerr << ex.what();
		std::cerr << "Error opening image file" << std::endl;
	}

	std::cerr << "\n\rRendering Completed..." << std::flush;
	imageFile.close();

	return 0;
}