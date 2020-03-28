#include <iostream>
#include <fstream>

#include "ray.h"

#define IMG_WIDTH 400
#define IMG_HEIGHT 200

// Creating the gradient texture.
vec3f color(const Ray& ray)
{
	vec3f normDirection = ray.direction();
	normDirection = normDirection.normalize();

	// normaldirection has range from [-1, 1] so bringing
	// it into the range ofo [0,1].
	float t = 0.5f * (normDirection.y() + 1.0f);

	// This basically is a lerp function.
	// Lerp : (1-t) * start + t * end; where t = Controlling Parameter.
	// t=0, color=vec3(1,1,1), multiplied by 255, the corresponding RGB is (255,255,255) = white color.  
	// t=1, color=vec3(0.5,0.7,1), multiplied by 255, corresponds to RGB (127.5,178.5,255) = sky blue color.  
	// The above two colors correspond to "white" and "light blue" respectively.  
	// The picture color = (1-t) * white + t * light blue, which is the result of the linear interpolation of the picture colors
	// "white" and "light blue" (along the Y direction). 
	return (1 - t) * vec3f(1.0f, 1.0f, 1.0f) + t * vec3f(0.5f, 0.7f, 1.0f);
}


int main(int argc, char* argv[])
{
	std::ofstream imageFile;
	try
	{
		imageFile.open("Output.ppm");
		if (imageFile)
		{
			imageFile << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n255\n";

			vec3f lower_left_corner(-2.0f, -1.0f, -1.0f);
			vec3f horizontal(4.0f, 0.0f, 0.0f);
			vec3f vertical(0.0f, 2.0f, 0.0f);
			vec3f origin(0.0f, 0.0f, 0.0f);

			// Y (Top to Bottom)
			// X (Left to right)
			for (int y=IMG_HEIGHT-1; y>=0; --y)
			{
				for (int x=0; x<IMG_WIDTH; ++x)
				{
					float u = float(x) / IMG_WIDTH;
					float v = float(y) / IMG_HEIGHT;

					Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
					vec3f col = color(ray);
					int r = int(255.99 * col[0]);
					int g = int(255.99 * col[1]);
					int b = int(255.99 * col[2]);

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

	imageFile.close();

	return 0;
}