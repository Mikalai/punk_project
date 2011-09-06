/*
	File: StaticMeshWithPerPixelLighting.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with multitexture support
*/
#ifndef _H_STATIC_MESH_WITH_PPL
#define _H_STATIC_MESH_WITH_PPL

class StaticMeshWithPerPixelLighting
{
public:
	StaticMeshWithPerPixelLighting(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithPerPixelLighting();
	GLuint m_normalizationCubeMap;
	GLuint m_bumpMap;
	float m_lightPos[3];
	int m_vertexCount;	
	int m_indexCount;
	float* m_vertex;
	float* m_texture;
	float* m_lightVector;
	float* m_normals;
	unsigned short* m_index;
	void Draw();
	void SetNormalizationMap(GLuint textureId);
	void SetBumpMap(GLuint textureId);
	void SetLightPos(float x, float y, float z);
	static StaticMeshWithPerPixelLighting* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_H_STATIC_MESH_WITH_PPL