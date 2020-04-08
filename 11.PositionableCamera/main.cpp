#include <iostream>
#include <fstream>

#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectic.h"

#define IMG_WIDTH 1200
#define IMG_HEIGHT 800
#define IMG_SAMPLES 10
#define max_depth 50

// Creating the gradient texture.
vec3d ray_color(const Ray& ray, const hitable& world, int depth)
{
	hit_record rec;

	// We don't exced the no of ray bounce limit, after that no
	// more light is gathered.
	if (depth <= 0)
		return vec3d(0, 0, 0);

	if (world.hit(ray, 0.001, infinity, rec))
	{
		Ray scattered;
		vec3d attenuation;
		if (rec.mat_ptr->scatter(ray, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, world, depth - 1);
		}
		return vec3d(0, 0, 0);
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
	imageFile.open("../Images/11.PositionableCamera.ppm");

	// Image Corner points.
	vec3d vUp(0, 1, 0);

	const auto aspectRatio = static_cast<double>(IMG_WIDTH)/ static_cast<double>(IMG_HEIGHT);
	Camera cam(vec3d(-2, 2, 1), vec3d(0, 0, -1), vUp, 90, aspectRatio);
	
	hitable_list world;
	world.AddObject(make_shared<sphere>(vec3d(0, 0, -1), 0.5, std::make_shared<lambertian>(vec3d(0.1, 0.2, 0.5))));
	world.AddObject(make_shared<sphere>(vec3d(0, -100.5, -1), 100, std::make_shared<lambertian>(vec3d(0.8, 0.8, 0.0))));
	world.AddObject(make_shared<sphere>(vec3d(1, 0, -1), 0.5, std::make_shared<metal>(vec3d(0.8, 0.6, 0.2), 0.0)));
	world.AddObject(make_shared<sphere>(vec3d(-1, 0, -1), 0.5, std::make_shared<dielectric>(1.5)));
	world.AddObject(make_shared<sphere>(vec3d(-1, 0, -1), -0.45, std::make_shared<dielectric>(1.5)));
		
	if (imageFile)
	{
		imageFile << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n";
		imageFile << "255" << "\n";

		// Pixel sampling average.
		auto scale = 1 / double(IMG_SAMPLES);

		// Starting the image file to bottom left to top right.
		for (int y = IMG_HEIGHT - 1; y >= 0; --y)
		{
			std::cout << "\rScanline Rendering Remaining: " << y << ' ' << '\n';
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
					col += ray_color(r, world, max_depth);
				}


				// Pixel sampling(antialiasing) and gamma corection of 2.
				auto r = sqrt(scale * col.x());
				auto g = sqrt(scale * col.y());
				auto b = sqrt(scale * col.z());

				// Again putting it in the value of 0-255.
				int iR = static_cast<int>(256 * clamp(r, 0.0, 0.999));
				int iG = static_cast<int>(256 * clamp(g, 0.0, 0.999));
				int iB = static_cast<int>(256 * clamp(b, 0.0, 0.999));

				imageFile << iR << " " << iG << " " << iB << "\n";
			}
		}
	}
	else
	{
		std::cout << "Error opening image file" << '\n';
	}

	std::cerr << "\n\rRendering Completed..." << std::flush;
	imageFile.close();

	return 0;
}