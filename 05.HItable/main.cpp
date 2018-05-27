#include <iostream>
#include <fstream>

#include "sphere.h"
#include "hitable_list.h"
#include "float.h"

// Image Width and Height.
#define IMG_WIDTH 600
#define IMG_HEIGHT 300

vec3 color(const Ray& r, hitable *world) 
{
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec)) 
	{
		return 0.5*vec3(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
	}
	else 
	{
		vec3 unit_direction = unit_vector(r.direction);
		float t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	// Creating a basic PPM image file with gradient color.
	std::ofstream imageFile;
	imageFile.open("image.ppm");

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);

	if (imageFile)
	{
		imageFile << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n";
		imageFile << "255" << "\n";

		for (int j = IMG_HEIGHT - 1; j >= 0; j--)
		{
			for (int i = 0; i < IMG_WIDTH; i++)
			{
				float u = float(i) / float(IMG_WIDTH);
				float v = float(j) / float(IMG_HEIGHT);
				Ray r(origin, lower_left_corner + u*horizontal + v*vertical);

				vec3 p = r.point_at_parameter(2.0);
				vec3 col = color(r, world);
				int ir = int(255.99*col.x);
				int ig = int(255.99*col.y);
				int ib = int(255.99*col.z);

				imageFile << ir << " " << ig << " " << ib << "\n";
			}
		}
	}
}