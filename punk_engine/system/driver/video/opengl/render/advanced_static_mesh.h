/*
	File: AdvancedStaticMesh.h"
	Author: Abramov Nickolai
	Description: Contains a class to represent a geometry
		data of static mesh with multitexture support. for
		drawing it use register combiner, that's cool.
		Use vbo to store data in video memory
*/
#ifndef _H_ADVANCED_STATIC_MESH
#define _H_ADVANCED_STATIC_MESH

#include "render_element.h"
#include "../driver/video/opengl/shader_program.h"
#include "../math/bounding_box.h"

namespace Render
{
    class AdvancedStaticMesh : public RenderElement
    {
    public:
	struct Vertex
	{
            float x, y, z;
            float nx, ny, nz;
            float tx, ty, tz;
            float bx, by, bz;
            float u, v;
            static const unsigned PositionOffset = 0;
            static const unsigned NormalOffset = 3*sizeof(float);
            static const unsigned TangentOffset = 6*sizeof(float);
            static const unsigned BinormalOffset = 9*sizeof(float);
            static const unsigned TextureOffset = 12*sizeof(float);
	};
    public:
	AdvancedStaticMesh();
	~AdvancedStaticMesh();
	ShaderProgram* m_program;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	GLuint m_vao;

	GLint m_vertexAttrib;
	GLint m_textureVertexAttrib;
	GLint m_normalAttrib;
	GLint m_tangentAttrib;
	GLint m_binormalAttrib;

	GLint m_baseMapUniform;
	GLint m_bumpMapUniform;

	GLint m_worldViewProjUniform;
	GLint m_normalUniform;
	GLint m_worldViewUniform;
	GLint m_lightDirUniform;
	GLint m_eyePositionUniform;
	GLint m_lightPositionUniform;
	GLint m_lightAmbientUniform;
	GLint m_lightDiffuseUniform;
	GLint m_lightSpecularUniform;
	GLint m_specularPowerUniform;

	GLuint m_baseMap;
	GLuint m_normalMap;

	Math::mat4 m_matrix;
	int m_vertexCount;
	int m_indexCount;
	Vertex* m_vertex;
	Math::BoundingBox m_bbox;
	unsigned short* m_index;
      
	virtual void Render();
	virtual void BindShaderData();
		
	static AdvancedStaticMesh* CreateFromFile(const char* filename);
	static AdvancedStaticMesh* CreateCube(float length, float width, float height, int lSeg, int wSeg, int hSeg);
	ShaderProgram* GetProgram();
	void SetProgram(ShaderProgram* program);
	void SetDecalMap(GLuint decal);
	void SetBumpMap(GLuint bump);
	void Init();
	void FlipNormals();
    private:
	void InternalDraw_v1();
	void InternalDraw_v2();
    };
}

#endif //	_H_STATIC_MESH_WITH_VBO
