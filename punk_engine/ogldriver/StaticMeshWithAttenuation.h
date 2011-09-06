/*
	File: StaticMeshWithAttenuation.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with multitexture support. for
		drawing it use register combiner, that's cool.
		Use vbo to store data in video memory
*/
#ifndef _H_STATIC_MESH_WITH_ATTENUATION
#define _H_STATIC_MESH_WITH_ATTENUATION

class StaticMeshWithAttenuation
{
public:
	StaticMeshWithAttenuation(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithAttenuation();
	GLuint m_decalMap;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	float m_lightRadius;
	float m_lightPos[3];
	int m_vertexCount;	
	int m_indexCount;
	float* m_vertex;
	float* m_normals;
	float* m_texture;
	float* m_lightVector;
	float* m_tangent;
	float* m_binormal;
	unsigned short* m_index;
	void Draw();
	void SetLightPos(float x, float y, float z);
	void SetDecalMap(GLuint decal);
	void SetLightRadius(float radius);
	static StaticMeshWithAttenuation* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_H_STATIC_MESH_WITH_VBO