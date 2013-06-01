#include "../PUNK_ENGINE_PUBLIC/images/images.h"
#include "../PUNK_ENGINE_PUBLIC/system/string.h"
#include "../PUNK_ENGINE_PUBLIC/system/system.h"
#include "../PUNK_ENGINE_PUBLIC/math/math.h"
#include "checker.h"

//
//	create checker desk
//

void CreateChecker(int argc, char** argv)
{
	if (argc != 8)
	{
		printf("for checker: %s width height checker output.png cell_size color1[0xRRGGBBAA] color2\n");
		return;
	}
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int cell_size = atoi(argv[5]);

	if (cell_size < 0)
	{
		printf("cell size can't be <= 0\n");
		return;
	}

	unsigned color1 = (unsigned)System::string(argv[6]).ToInt32FromHex();
	unsigned color2 = (unsigned)System::string(argv[7]).ToInt32FromHex();

	ImageModule::PngFile png;
	png.SetSize(width, height);
	png.SetFormat(ImageModule::IMAGE_FORMAT_RGBA);

	unsigned char* c1 = (unsigned char*)&color1;
	unsigned char* c2 = (unsigned char*)&color2;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if ((x / cell_size) % 2 == 0)
			{
				if ((y / cell_size) % 2 == 0)
				{
					png.SetPixel(x, y, c1[3], c1[2], c1[1], c1[0]);
				}
				else
				{
					png.SetPixel(x, y, c2[3], c2[2], c2[1], c2[0]);
				}
			}
			else
			{
				if ((y / cell_size) % 2 == 0)
				{
					png.SetPixel(x, y, c2[3], c2[2], c2[1], c2[0]);
				}
				else
				{
					png.SetPixel(x, y, c1[3], c1[2], c1[1], c1[0]);
				}
			}
		}
	}
	png.Save(System::string(argv[4]).Data());
}
