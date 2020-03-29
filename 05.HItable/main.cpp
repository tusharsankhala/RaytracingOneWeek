#include <iostream>
#include <fstream>

#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include <limits>

#define IMG_WIDTH 400
#define IMG_HEIGHT 200

// Creating the gradient texture.
vec3f color(const Ray& ray, hitable* world)
{
	hit_record rec;

	// Getting the nearest hit point to no hit point at all.
	if (world->hit(ray, 0.0, std::numeric_limits<float>::max(), rec))
	{
		return 0.5f * vec3f(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		vec3f ray_NormDir = ray.direction();
		ray_NormDir = ray_NormDir.normalize();

		// Since the value of y is -1 to 1, we used a common normalization trick here to remap to (0,1).
		float t = 0.5f * (ray_NormDir.y() + 1.0f);

		// This basically is a lerp function.
		// Lerp : (1-t) * start + t * end; where t = Controlling Parameter.
		// t=0, color=vec3(1,1,1), multiplied by 255, the corresponding RGB is (255,255,255)  
		// t=1, color=vec3(0.5,0.7,1), multiplied by 255, corresponds to RGB (127.5,178.5,255)  
		// The above two colors correspond to "white" and "light blue" respectively.  
		// The picture color = (1-t)* "white" + t* "light blue", which is the result of the linear interpolation of the picture colors "white" and "light blue" (along the Y direction). 
		// If you want to change to X or Z direction, change the above .y() to .x() or .z().
		// To change other colors, set the corresponding RGB value.
		return ((1.0f - t) * vec3f(1.0f, 1.0f, 1.0f) + vec3f(0.5f, 0.7f, 1.0f) * t);
	}	
}

int main(int argc, char* argv[])
{

	// Creating a basic PPM image file with gradient color.
	std::ofstream imageFile;
	imageFile.open("image_Hitable.ppm");

	if (imageFile)
	{
		// Image Corner points.
		vec3f lower_left_corner(-2.0, -1.0, -1.0);
		vec3f horizontal(4.0, 0.0, 0.0);
		vec3f vertical(0.0, 2.0, 0.0);	
		vec3f origin(0.0, 0.0, 0.0);
		hitable* list[2];
		list[0] = new sphere(vec3f(0.0f, 0.0f, -1.0f), 0.5f);
		list[1] = new sphere(vec3f(0.0f, -100.5f, -1.0f), 100.0f);

		hitable* world = new hitable_list(list, 2);

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
				vec3f p = r.point_at_parameter(2.0);
				vec3f col = color(r, world);

				// Again putting it in the value of 0-255.
				int iR = int(col.x() * 255.99);
				int iG = int(col.y() * 255.99);
				int iB = int(col.z() * 255.99);

				imageFile << iR << " " << iG << " " << iB << "\n";
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