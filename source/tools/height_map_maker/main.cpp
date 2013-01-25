#include "../../punk_engine.h"
#include <algorithm>

void GenerateHeightMap(int argc, char* argv[])
{
	int dim = 512;
	int size = 512;
	int blocks = 1;
	int seed = 1;
	float height_scale = 1000;
	Math::vec2 origin(0,0);
	System::string name(L"test_map");

	for (int i = 2; i < argc; ++i)
	{
		if (!strcmp(argv[i], "/blocks"))
		{
			blocks = atoi(argv[++i]);
		}
		else if (!strcmp(argv[i], "/size"))
		{
			size = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "/seed"))
		{
			seed = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "/name"))
		{
			name = System::string(argv[++i]);
		}
	}

	float scale = 2;

	System::string path = System::Environment::Instance()->GetMapFolder() + name + L"\\";
	System::Folder f;
	if (!f.Open(path))
	{
		out_error() << "Can't open folder " << path << std::endl;
		return;
	}

	Virtual::Terrain terrain;
	terrain.SetNumBlocks(blocks);
	terrain.SetBlockScale((float)size / (float)dim);
	terrain.SetHeightScale(height_scale);
	terrain.SetOrigin(origin);	
	
	System::Buffer data(size*size*sizeof(float));
	data.SetPosition(size*size*sizeof(float));
	// iterate through each block
	for (int y_block = 0; y_block < blocks; ++y_block)
	{
		for (int x_block = 0; x_block < blocks; ++x_block)
		{
			Virtual::TerrainCell* cell = terrain.GetCell(x_block, y_block);
			//	create raw file
			System::string filename_raw = System::string::Format(L"%d_%d.raw", x_block, y_block);
			System::string filename_png = System::string::Format(L"%d_%d.png", x_block, y_block);
			System::string name = System::string::Format(L"cell_%d_%d", x_block, y_block);

			ImageModule::GrayImage image;
			image.SetSize(size, size);

			Math::Noise noise(1);			
			noise.GenerateHeightMap(x_block * scale, y_block * scale, scale, scale, size, size, (float*)data.StartPointer());

			//noise.SetPersistance(1.0/16.0);
			//noise.SetOctavesCount(8);
			
			auto minmax = std::minmax_element(data.begin<float>(), data.end<float>());
			auto minv = *minmax.first;
			auto maxv = *minmax.second;

			System::BinaryFile::Save(filename_raw, data);
	
			////	normalize
			
			std::transform(data.begin<float>(), data.end<float>(), data.begin<float>(), [&maxv, &minv] (float v) -> float 
			{ 				
				return (v - minv) / (maxv - minv);
			});

			///*std::transform(data.begin(), data.end(), data.begin(), [&maxv, &minv] (float v) -> float 
			//{ 
			//	float t = v;
			//	return std::min(1.0f, std::max(0.0f, t));
			//});*/

			//	copy to image
			for (int y = 0; y < size; ++y)
			{
				for (int x = 0; x < size; ++x)
				{
					float v = *(data.begin<float>() + x + y*size);
					if (v < 0 || v > 1)
						std::cout << v << ' ';

					image.SetPixelComponent(x, y, 0, 255.0 * v);
				}
			}

			ImageModule::Exporter exporter;
			exporter.Export(filename_png, image);

			cell->SetLocation(Math::ivec2(x_block, y_block));
			cell->SetBaseHeight(0);
			cell->SetName(name);
			Virtual::TerrainRawDataSource source;
			source.SetRawFile(filename_raw);
			cell->SetRawDataSource(source);
		}
	}
		
	std::wofstream stream("map.description", std::ios_base::binary);
	stream << terrain.ToString().Data();
	stream.close();

	std::ofstream stream2("map2.description", std::ios_base::binary);
	terrain.Save(stream2);
	stream2.close();

	f.Close();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		out_error() << "Should be *.exe [command], \n where command is -gen, -stitch" << std::endl;
		return 0;
	}
	
	if (!strcmp(argv[1], "-gen"))
	{
		GenerateHeightMap(argc, argv);
	}

	return 0;
}