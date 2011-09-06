/*
	File: StaticMeshWithPerPixelLightingAndTexture.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with multitexture support
*/
#ifndef _H_STATIC_MESH_WITH_PPL_AND_T
#define _H_STATIC_MESH_WITH_PPL_AND_T

class StaticMeshWithPerPixelLightingAndTexture
{
public:
	StaticMeshWithPerPixelLightingAndTexture(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithPerPixelLightingAndTexture();
	GLuint m_normalizationCubeMap;
	GLuint m_bumpMap;
	GLuint m_decal;
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
	void SetDecal(GLuint textureId);
	void SetLightPos(float x, float y, float z);
	static StaticMeshWithPerPixelLightingAndTexture* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_H_STATIC_MESH_WITH_PPL_AND_T