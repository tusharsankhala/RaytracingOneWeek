#include <iostream>
#include <fstream>

#include "vec3.h"

#define IMG_WIDTH 200
#define IMG_HEIGHT 100

int main(int argc, char* argv[])
{

	// Creating a basic PPM image file with gradient color.
	std::ofstream imageFile;
	imageFile.open("image.ppm");

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
				float normR = float(x) / float(IMG_WIDTH);
				float normG = float(y) / float(IMG_HEIGHT);
				float normB = 0.2f;

				// Again putting it in the value of 0-255.
				int iR = int(normR*255.99);
				int iG = int(normG*255.99);
				int iB = int(normB*255.99);

				imageFile << iR << " " << iG << " " << iB << "\n";
				std::cout << iR << " " << iG << " " << iB << "\n";
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