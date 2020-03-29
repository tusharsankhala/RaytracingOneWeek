#include <iostream>
#include <fstream>
#include <exception>

#include "vec3.h"

#define IMG_WIDTH 400
#define IMG_HEIGHT 200

int main(int argc, char* argv[])
{
	std::ofstream imageFile;

	try
	{
		imageFile.open("Output_02Vec3.ppm");
		if (imageFile)
		{
			imageFile << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n255\n";

			// Y (Top to Bottom)
			// X (Left to right)
			for (int y = IMG_HEIGHT - 1; y >= 0; --y)
			{
				std::cerr << "\rScanline Rendering Remaining: " << y << ' ' << std::flush;
				for (int x = 0; x < IMG_WIDTH; ++x)
				{
					vec3d col(double(x) / IMG_WIDTH, double(y) / IMG_HEIGHT, 0.2);
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