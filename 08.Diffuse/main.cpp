#include <iostream>
#include <fstream>

#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "float.h"


// Image Width and Height.
#define IMG_WIDTH 400
#define IMG_HEIGHT 200
#define NUM_SAMPLES 100

#define srand48(x) srand((int)(x))
#define drand48() ((double)rand()/RAND_MAX)


// Getting the random point in the unit cube in the range of -1 to +1 in x,yxand z direction.
// Condition:
// Accept the point: if the point lies in the unit sphere.
// Reject the point: if the point lies outside the unit sphere.
vec3f random_unit_in_sphere()
{
	vec3f p;
	do
	{
		p = 2.0f * vec3f(drand48(), drand48(), drand48()) - vec3f(1.0f, 1.0f, 1.0f);
	} while (p.dot(p) >= 1.0f);

	return p;
}


vec3f color(const Ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec))
	{
		vec3f target = rec.p + rec.normal + random_unit_in_sphere();
		return 0.5f * color(Ray(rec.p, target-rec.p), world);
	}
	else
	{
		vec3f unit_direction = unit_vector(r.direction);
		float t = 0.5f * (unit_direction.y + 1.0f);
		return (1.0f - t) * vec3f(1.0f, 1.0f, 1.0f) + t * vec3f(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	// Creating a basic PPM image file with gradient color.
	std::ofstream imageFile;
	imageFile.open("image.ppm");


	hitable *list[2];
	list[0] = new sphere(vec3f(0, 0, -1), 0.5);
	list[1] = new sphere(vec3f(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	Camera cam;

	if (imageFile)
	{
		imageFile << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n";
		imageFile << "255" << "\n";

		for (int j = IMG_HEIGHT - 1; j >= 0; j--)
		{
			for (int i = 0; i < IMG_WIDTH; i++)
			{
				vec3f col(0.0f, 0.0f, 0.0f);

				for (int h = 0; h < NUM_SAMPLES; h++)
				{
					float u = float(i + drand48()) / float(IMG_WIDTH);
					float v = float(j + drand48()) / float(IMG_HEIGHT);
					Ray r = cam.get_ray(u, v);
					vec3f p = r.point_at_parameter(2.0);
					col += color(r, world);
				}

				col /= float(NUM_SAMPLES);
				col = vec3f(sqrtf(col.x), sqrtf(col.y), sqrtf(col.z));
				int ir = int(255.99*col.x);
				int ig = int(255.99*col.y);
				int ib = int(255.99*col.z);

				imageFile << ir << " " << ig << " " << ib << "\n";
				std::cout << ir << " " << ig << " " << ib << "\n";
			}
		}
	}
}