/*
	File: StaticMesh.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh
*/
#ifndef _H_STATIC_MESH
#define _H_STATIC_MESH

class StaticMesh
{
public:
	StaticMesh(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMesh();
	int m_vertexCount;
	int m_indexCount;
	float* m_vertex;
	float* m_texture;
	float* m_normals;
	unsigned short* m_index;
	void Draw();

	static StaticMesh* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();
};

#endif //_H_STATIC_MESH
