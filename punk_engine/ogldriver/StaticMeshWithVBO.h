/*
	File: StaticMeshWithVBO.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with multitexture support. for
		drawing it use register combiner, that's cool.
		Use vbo to store data in video memory
*/
#ifndef _H_STATIC_MESH_WITH_VBO
#define _H_STATIC_MESH_WITH_VBO

class StaticMeshWithVBO
{
public:
	StaticMeshWithVBO(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	~StaticMeshWithVBO();
	GLuint m_normalizationCubeMap;
	GLuint m_bumpMap;
	GLuint m_decalMap;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	float m_eye[3];
	float m_lightPos[3];
	float m_lightColor[4];
	float m_ambientColor[4];
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
	void SetNormalizationMap(GLuint textureId);
	void SetBumpMap(GLuint textureId);
	void SetLightPos(float x, float y, float z);
	void SetLightColor(const float* color);
	void SetAmbientColor(const float* color);
	void SetEye(const float* eye);
	void SetDecalMap(GLuint decal);
	static StaticMeshWithVBO* CreateFromFile(const char* filename);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();	
};

#endif //	_H_STATIC_MESH_WITH_VBO