/*
	File: StaticMeshWithPerPixelLightingAndSelfShading.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with multitexture support. for
		drawing it use register combiner, that's cool
*/
#ifndef _H_STATIC_MESH_WITH_PPL_AND_SELF_SHADING
#define _H_STATIC_MESH_WITH_PPL_AND_SELF_SHADING

class StaticMeshWithPerPixelLightingAndSelfShading
{
public:
	StaticMeshWithPerPixelLightingAndSelfShading(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithPerPixelLightingAndSelfShading();
	GLuint m_normalizationCubeMap;
	GLuint m_bumpMap;
	float m_lightPos[3];
	float m_lightColor[4];
	float m_ambientColor[4];
	int m_vertexCount;	
	int m_indexCount;
	float* m_vertex;
	float* m_texture;
	float* m_lightVector;
	float* m_normals;
	float* m_tangent;
	float* m_binormal;
	unsigned short* m_index;
	void Draw();
	void SetNormalizationMap(GLuint textureId);
	void SetBumpMap(GLuint textureId);
	void SetLightPos(float x, float y, float z);
	void SetLightColor(float* color);
	void SetAmbientColor(float* color);
	static StaticMeshWithPerPixelLightingAndSelfShading* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_H_STATIC_MESH_WITH_PPL2