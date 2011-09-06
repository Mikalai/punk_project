/*
	File: StaticMeshWithTBN.h
	Author: Abramov Nickolai
	Description: Contains mesh description with possibility of applying a
		bump map effect
*/

#ifndef _H_STATIC_MESH_WITH_TBN
#define _H_STATIC_MESH_WITH_TBN

class StaticMeshWithTBN
{
public:
	StaticMeshWithTBN(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithTBN();
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
	float* m_tangent;
	float* m_binormal;
	unsigned short* m_index;
	void Draw();
	void SetNormalizationMap(GLuint textureId);
	void SetBumpMap(GLuint textureId);
	void SetDecal(GLuint textureId);
	void SetLightPos(float x, float y, float z);
	static StaticMeshWithTBN* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_STATIC_MESH_WITH_TBN