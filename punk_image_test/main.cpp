#include <stdio.h>
#include "../punk_engine/images/images.h"

int main()
{
	try
	{
		Image::PngFile file;
		file.Load(L"E:\\project\\textures\\grass_256x256.png");
		printf("File loaded\n");
		file.Save(L"E:\\project\\textures\\grass_256x256_yo.png");
		printf("File saved\n");
	}
	catch(Image::ImageError& err)
	{
		wprintf(L"Error: %s\n", err.w_what());
	}
	return 0;
}