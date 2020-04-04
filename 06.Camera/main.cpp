#include <iostream>
#include <fstream>

#include "Constants.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"

#define IMG_WIDTH 400
#define IMG_HEIGHT 200
#define IMG_SAMPLES 100

// Creating the gradient texture.
vec3d ray_color(const Ray& ray, const hitable& world)
{
	hit_record rec;
	if (world.hit(ray, 0, infinity, rec))
	{
		// Normalize the result from (-1,1) to (0, 1).
		return 0.5 * (rec.normal + vec3d(1, 1, 1));
	}
	vec3d unit_direction = normalize(ray.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);

	// This basically is a lerp function.
	// Lerp : (1-t) * start + t * end; where t = Controlling Parameter.
	// t=0, color=vec3(1,1,1), multiplied by 255, the corresponding RGB is (255,255,255)  
	// t=1, color=vec3(0.5,0.7,1), multiplied by 255, corresponds to RGB (127.5,178.5,255)  
	// The above two colors correspond to "white" and "light blue" respectively.  
	// The picture color = (1-t)* "white" + t* "light blue", which is the result of the linear interpolation of the picture colors "white" and "light blue" (along the Y direction). 
	// If you want to change to X or Z direction, change the above .y() to .x() or .z().
	// To change other colors, set the corresponding RGB value.
	return (1.0 - t) * vec3d(1.0, 1.0, 1.0) + t * vec3d(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{

	// Creating a basic PPM image file with gradient color.
	std::ofstream imageFile;
	imageFile.open("../Images/07.Antialiasing.ppm");

	// Image Corner points.
	vec3d lower_left_corner(-2.0, -1.0, -1.0);
	vec3d vertical(0.0, 2.0, 0.0);
	vec3d horizontal(4.0, 0.0, 0.0);
	vec3d origin(0.0, 0.0, 0.0);

	hitable_list world;
	world.AddObject(make_shared<sphere>(vec3d(0, 0, -1), 0.5));
	world.AddObject(make_shared<sphere>(vec3d(0, -100.5, -1), 100));

	Camera cam;
	if (imageFile)
	{
		imageFile << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n";
		imageFile << "255" << "\n";

		// Starting the image file to bottom left to top right.
		for (int y = IMG_HEIGHT - 1; y >= 0; --y)
		{
			std::cerr << "\rScanline Rendering Remaining: " << y << ' ' << std::flush;
			for (int x = 0; x < IMG_WIDTH; ++x)
			{
				vec3d col(0, 0, 0);

				// Samples.
				for (int s = 0; s < IMG_SAMPLES; ++s)
				{ 
					// Normalizing the value.
					auto u = (x + random_double()) / IMG_WIDTH;
					auto v = (y + random_double()) / IMG_HEIGHT;

					Ray r = cam.get_ray(u, v);
					col += ray_color(r, world);
				}

				// Averaging the color.
				col /= double(IMG_SAMPLES);

				// Again putting it in the value of 0-255.
				int iR = static_cast<int>(256 * clamp(col.x(), 0.0, 0.999));
				int iG = static_cast<int>(256 * clamp(col.y(), 0.0, 0.999));
				int iB = static_cast<int>(256 * clamp(col.z(), 0.0, 0.999));

				imageFile << iR << " " << iG << " " << iB << "\n";
			}
		}
	}
	else
	{
		std::cout << "Error opening image file" << std::endl;
	}

	std::cerr << "\n\rRendering Completed..." << std::flush;
	imageFile.close();

	return 0;
}