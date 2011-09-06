/*
	File: StaticMeshWithEnvironmentMap.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with one color texture and evironment map
*/

#ifndef _H_STATIC_MESH_WITH_ENV
#define _H_STATIC_MESH_WITH_ENV

class StaticMeshWithEnvironmentMap
{
public:
	StaticMeshWithEnvironmentMap(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithEnvironmentMap();
	int m_maxTextures;
	GLuint m_textureIndexArray[2];
	int m_vertexCount;	
	int m_indexCount;
	float* m_vertex;
	float* m_texture;
	float* m_normals;
	unsigned short* m_index;
	void Draw();
	void SetTexture(GLuint textureId);
	void SetEnvironmentMap(GLuint textureId);
	static StaticMeshWithEnvironmentMap* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_H_STATIC_MESH_WITH_ENV