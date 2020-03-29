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
		imageFile.open("Output_01Start.ppm");
		if (imageFile)
		{
			imageFile << "P3\n" << IMG_WIDTH <<  " " << IMG_HEIGHT << "\n255\n";
			
			// Y (Top to Bottom)
			// X (Left to right)
			for (int y = IMG_HEIGHT - 1; y >= 0; --y)
			{
				std::cerr << "\rScanline Rendering Remaining: " << y << ' ' << std::flush;
				for (int x = 0; x < IMG_WIDTH; ++x)
				{
					auto ir = double(x) / IMG_WIDTH;
					auto ig = double(y) / IMG_HEIGHT;
					auto ib = 0.2;

					int r = static_cast<int>(255.99 * ir);
					int g = static_cast<int>(255.99 * ig);
					int b = static_cast<int>(255.99 * ib);

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

	std::cerr << "\n\rRendering Finished: " << std::endl;
	imageFile.close();

	return 0;
}