/*
	File: StaticMeshWithCubeMap.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with multitexture support
*/
#ifndef _H_STATIC_MESH_WITH_CUBE_MAP
#define _H_STATIC_MESH_WITH_CUBE_MAP

class StaticMeshWithCubeMap
{
public:
	StaticMeshWithCubeMap(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithCubeMap();
	GLuint m_cubeMap;
	int m_vertexCount;	
	int m_indexCount;
	float* m_vertex;
	float* m_texture;
	float* m_normals;
	unsigned short* m_index;
	void Draw();
	void SetCubeMap(GLuint textureId);
	static StaticMeshWithCubeMap* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_H_STATIC_MESH_WITH_CUBE_MAP