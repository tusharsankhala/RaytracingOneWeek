#include <iostream>
#include <fstream>
#include <exception>

#define IMG_WIDTH 400
#define IMG_HEIGHT 200

int main(int argc, char* argv[])
{
	std::ofstream imageFile; 

	try
	{
		imageFile.open("Output.ppm");
		if (imageFile)
		{
			imageFile << "P3\n" << IMG_WIDTH <<  " " << IMG_HEIGHT << "\n255\n";
			
			// Y (Top to Bottom)
			// X (Left to right)
			for (int y = IMG_HEIGHT - 1; y >= 0; --y)
			{
				for (int x = 0; x < IMG_WIDTH; ++x)
				{
					float ir = float(x) / IMG_WIDTH;
					float ig = float(y) / IMG_HEIGHT;
					float ib = 0.2f;

					int r = int(255.99 * ir);
					int g = int(255.99 * ig);
					int b = int(255.99 * ib);

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