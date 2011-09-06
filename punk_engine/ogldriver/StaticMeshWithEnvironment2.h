/*
	File: StaticMeshWithEnvironment2.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with one color texture and evironment map
*/

#ifndef _H_STATIC_MESH_WITH_ENV2
#define _H_STATIC_MESH_WITH_ENV2

class StaticMeshWithEnvironment2
{
public:
	StaticMeshWithEnvironment2(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithEnvironment2();
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
	static StaticMeshWithEnvironment2* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_H_STATIC_MESH_WITH_ENV2