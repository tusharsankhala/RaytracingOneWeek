#include <iostream>
#include <fstream>

#include "ray.h"

#define IMG_WIDTH 400
#define IMG_HEIGHT 200

// Creating the gradient texture.
vec3d color(const Ray& ray)
{
	vec3d normDirection = ray.direction();
	normDirection = normDirection.normalize();

	// normaldirection has range from [-1, 1] so bringing
	// it into the range ofo [0,1].
	double t = 0.5 * (normDirection.y() + 1.0);

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
		imageFile.open("Output_03Ray.ppm");
		if (imageFile)
		{
			imageFile << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n255\n";

			vec3d lower_left_corner(-2.0, -1.0, -1.0);
			vec3d horizontal(4.0, 0.0, 0.0);
			vec3d vertical(0.0, 2.0, 0.0);
			vec3d origin(0.0, 0.0, 0.0);

			// Y (Top to Bottom)
			// X (Left to right)
			for (int y=IMG_HEIGHT-1; y>=0; --y)
			{
				std::cerr << "\rScanline Rendering Remaining: " << y << ' ' << std::flush;
				for (int x=0; x<IMG_WIDTH; ++x)
				{
					auto u = double(x) / IMG_WIDTH;
					auto v = double(y) / IMG_HEIGHT;

					Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
					vec3d col = color(ray);
					auto r = static_cast<int>(255.99 * col[0]);
					auto g = static_cast<int>(255.99 * col[1]);
					auto b = static_cast<int>(255.99 * col[2]);

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