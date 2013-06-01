//#include "../system/system.h"
//#include "generator.h"
//
//namespace Generator
//{
//	Common::StaticGeometry* Creator::GenerateBox(float width, float height, float depth)
//	{
//		Common::StaticGeometry* geom = new Common::StaticGeometry;
//
//		Common::StaticGeometry::Vertex* vertex = new Common::StaticGeometry::Vertex[36];
//
//		vertex[0].x = -width/2;
//
//		return geom;
//	}
//
//	Common::StaticGeometry* Creator::GeneratPlane(float width, float height, int width_slice, int height_slice)
//	{
//		Common::StaticGeometry* geom = new Common::StaticGeometry;
//
//		Common::StaticGeometry::Vertex* v = new Common::StaticGeometry::Vertex[(width_slice+1)*(height_slice+1)];
//
//		for (int i = 0; i < height_slice + 1; i++)
//		{
//			for (int j = 0; j < width_slice + 1; j++)
//			{
//				v[i*(width_slice+1) + j].x = width/float(width_slice)*float(j);
//				v[i*(width_slice+1) + j].y = 0;
//				v[i*(width_slice+1) + j].z = height/float(height_slice)*float(i);
//				v[i*(width_slice+1) + j].nx = v[i*(width_slice+1) + j].nz = 0;
//				v[i*(width_slice+1) + j].ny = 1.0f;
//				v[i*(width_slice+1) + j].u = 1.0f/float(width_slice)*float(j);
//				v[i*(width_slice+1) + j].v = 1.0f/float(height_slice)*float(i);
//				v[i*(width_slice+1) + j].ix = (i + j) % 2; /*((i == 0) || (j == 0) || (i == height_slice) || (j == width_slice)) &&
//					!((i == 0 && j == 0) || ( i == height_slice && j == 0) || (i == height_slice && j == width_slice) || (i == 0 && j == width_slice))*/;
//			}
//		}
//
//		unsigned short int* index = new unsigned short[6*width_slice*height_slice];
//
//		for (int i = 0; i < height_slice; i++)
//		{
//			for (int j = 0; j < width_slice; j++)
//			{
//				index[6*(i*width_slice + j) + 0] = i*(width_slice+1) + j + 0;
//				index[6*(i*width_slice + j) + 1] = (i+1)*(width_slice+1) + j;
//				index[6*(i*width_slice + j) + 2] = i*(width_slice+1) + j + 1;
//
//				index[6*(i*width_slice + j) + 3] = i*(width_slice+1) + j + 1;
//				index[6*(i*width_slice + j) + 4] = (i+1)*(width_slice+1) + j;
//				index[6*(i*width_slice + j) + 5] = (i+1)*(width_slice+1) + j + 1;
//			}
//		}
//
//		geom->Set(v, (width_slice+1)*(height_slice+1), index, 6*width_slice*height_slice);
//
//		delete[] index;
//		delete[] v;
//
//		return geom;
//	}
//}
