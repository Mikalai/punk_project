/*
	File: StaticMeshWithTexture2.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with multitexture support. another one plagiat.
*/
#ifndef _H_STATIC_MESH_WITH_MT2
#define _H_STATIC_MESH_WITH_MT2

class StaticMeshWithTexture2
{
public:
	StaticMeshWithTexture2(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithTexture2();
	GLuint m_textureIndexArray[2];
	int m_vertexCount;	
	int m_indexCount;
	float m_color[4];
	float* m_vertex;
	float* m_texture;
	float* m_normals;
	unsigned short* m_index;
	void Draw();
	void SetTexture(int texturePos, GLuint textureId);
	void SetColor(float* color);
	static StaticMeshWithTexture2* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_H_STATIC_MESH_WITH_MT2