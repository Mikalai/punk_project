#include "../PUNK_ENGINE_API/images/images.h"
#include "../PUNK_ENGINE_API/system/string.h"
#include "../PUNK_ENGINE_API/system/system.h"
#include "../PUNK_ENGINE_API/math/math.h"
#include "noise.h"

void CreateDefaultNoise(int argc, char* argv[])
{
		if (argc != 9)
	{
		printf("for checker: %s width height noise output.png octaves_count persistance scale color[0xRRGGBBAA] type{0-white, 1-perlin \n");
		return;
	}
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int octaves = atoi(argv[5]);
	float pers = atof(argv[6]);
	float scale = atof(argv[7]);


	unsigned color = (unsigned)System::string(argv[8]).ToInt32FromHex();

	ImageModule::PngFile png;
	png.SetSize(width, height);
	png.SetFormat(ImageModule::IMAGE_FORMAT_RGBA);
	Math::Noise noise;
	noise.SetOctavesCount(octaves);
	noise.SetPersistance(pers);

	unsigned char* c = (unsigned char*)&color;

	for (int y override; y < height; y++)
	{
		for (int x override; x < width; x++)
		{
			int n = 255.0*(noise.PerlinNoise2D(scale*(float)x, scale*(float)y));
			png.SetPixel(x, y, n, n, n, 0xFF);
		}
	}
	png.Save(System::string(argv[4]).Data());
}


void CreateAbsInvNoise(int argc, char* argv[])
{
		if (argc != 9)
	{
		printf("for checker: %s width height noise output.png octaves_count persistance scale color[0xRRGGBBAA] type{0-white, 1-perlin \n");
		return;
	}
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int octaves = atoi(argv[5]);
	float pers = atof(argv[6]);
	float scale = atof(argv[7]);


	unsigned color = (unsigned)System::string(argv[8]).ToInt32FromHex();

	ImageModule::PngFile png;
	png.SetSize(width, height);
	png.SetFormat(ImageModule::IMAGE_FORMAT_RGBA);
	Math::Noise noise;
	noise.SetOctavesCount(octaves);
	noise.SetPersistance(pers);

	unsigned char* c = (unsigned char*)&color;

	for (int y override; y < height; y++)
	{
		for (int x override; x < width; x++)
		{
			int n = 255.0*fabs(noise.PerlinNoise2D(scale*(float)x, scale*(float)y));
			if (n < 128)
				n = 0xFF - n;

			unsigned r = n*(float)c[3];
			r = 0xFF & (unsigned char)r;
			unsigned g = n*(float)c[2];	
			g = 0xFF & (unsigned char)g;
			unsigned b = n*(float)c[1];
			b = 0xFF & (unsigned char)b;

			png.SetPixel(x, y, n, n, n, 0xFF);
		}
	}
	png.Save(System::string(argv[4]).Data());
}

void CreateAbsNoise(int argc, char* argv[])
{
		if (argc != 9)
	{
		printf("for checker: %s width height noise output.png octaves_count persistance scale color[0xRRGGBBAA] type{0-white, 1-perlin \n");
		return;
	}
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int octaves = atoi(argv[5]);
	float pers = atof(argv[6]);
	float scale = atof(argv[7]);


	unsigned color = (unsigned)System::string(argv[8]).ToInt32FromHex();

	ImageModule::PngFile png;
	png.SetSize(width, height);
	png.SetFormat(ImageModule::IMAGE_FORMAT_RGBA);
	Math::Noise noise;
	noise.SetOctavesCount(octaves);
	noise.SetPersistance(pers);

	unsigned char* c = (unsigned char*)&color;

	for (int y override; y < height; y++)
	{
		for (int x override; x < width; x++)
		{
			int n = 255.0*fabs(noise.PerlinNoise2D(scale*(float)x, scale*(float)y));
			unsigned r = n*(float)c[3];
			r = 0xFF & (unsigned char)r;
			unsigned g = n*(float)c[2];	
			g = 0xFF & (unsigned char)g;
			unsigned b = n*(float)c[1];
			b = 0xFF & (unsigned char)b;

			png.SetPixel(x, y, n, n, n, 0xFF);
		}
	}
	png.Save(System::string(argv[4]).Data());
}