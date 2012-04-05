#include <iostream>
#include <fstream>
#include <tchar.h>
#include "../utility/model/punk_scene_loader.h"
#include "../system/binary_file.h"
#include "../system/error.h"
#include "../images/images.h"

using namespace Math;

unsigned char convert(float min_z, float max_z, float z)
{
	return (unsigned char)((z - min_z) / (max_z - min_z) * 255.0f);
}

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cout << "Error: cmd = *.exe terrain.pmd size output.png" << std::endl << "Example: *.exe terrain.pmd 512 terrain.png" << std::endl;
		return -1;
	}

	try
	{
		Utility::Model mdl;
		std::cout << "Loading model...";
		mdl.LoadPunkModel(System::string(argv[1]));	
		std::cout << "Ok" << std::endl << "Building OctTree...";
		mdl.BuildOctTree();
		std::cout << "Ok" << std::endl;

		vec3 min = mdl.m_bbox.Min();
		vec3 max = mdl.m_bbox.Max();
		unsigned size = atoi(argv[2]);
		if (size <= 0)
		{
			std::cout << "Bad size" << std::endl;
		}
		float min_z = min.Z() - 1;
		float max_z = max.Z() + 1;

		float dx = (max.X() - min.X()) / (float)(size);
		float dy = (max.Y() - min.Y()) / (float)(size);
		
		float true_min = max_z;
		float true_max = min_z;
		float* points = new float[size*size];		
		for (int iy = 0; iy < size; ++iy)
		{
			//if (iy != 63)
			//	continue;
			//std::cout << "Current line: " << iy << std::endl;
			for (int ix = 0; ix < size; ++ix)
			{				/*
				if (ix == 65)
					ix = ix;*/
			//	std::cout << "Current row: " << ix;
				float x = min.X() + dx * (float)(ix);
				float y = min.Y() + dy * (float)(iy);
				std::vector<vec3> res;
				if (mdl.IntersectWithRay(vec3(x, y, min_z), vec3(x, y, max_z), res))
				{
					//std::cout <<" Points: " << res.size() << std::endl;
					points[iy*size+ix] = res[0].Z();
					if (true_min > res[0].Z())
						true_min = res[0].Z();
					if (true_max < res[0].Z())
						true_max = res[0].Z();
				}
				else
				{
					std::cout << " NO POINTS " << ix << std::endl;
					points[iy*size+ix] = true_min;
				}
				
			}
		}

		ImageModule::GrayImage image;
		image.SetSize(size, size);

		for (int iy = 0; iy < size; ++iy)
		{
			for (int ix = 0; ix < size; ++ix)
			{
				*image.GetPixelComponent(ix, iy, 0) = convert(true_min, true_max, points[iy*size+ix]);
			}
		}

		ImageModule::Exporter exporter;
		exporter.Export(System::string(argv[3]), image);

		std::ofstream stream("map.desc");
		stream << "map " << argv[3] << std::endl;
		stream << "size " << max.X() - min.X() << " " << max.Y() - min.Y() << std::endl;
		stream << "height " << min.Z() << " " << max.Z() << std::endl;
		stream.close();
	}
	catch(System::SystemError& error)
	{
		_tprintf(L"%s\n", error.Message().Data());
	}
	catch(wchar_t* l)
	{
		std::cout << "SDGHSDFGSDF" << l << std::endl;		
	}
	catch(char* l)
	{
		std::cout << "FFFFFFFFFFFFF" << l << std::endl;
	}
	catch(...)
	{
		std::cout << "Everything just died..." << std::endl;
	}

	return 0;
}