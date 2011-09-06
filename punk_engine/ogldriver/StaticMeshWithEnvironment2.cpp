/*
	File: StaticMeshWithEnvironment2
	Author: Abramov Nickolai
	Description: Implementation using texture combiner
*/

#include "Os.h"
#include "StaticMeshWithEnvironment2.h"

StaticMeshWithEnvironment2::StaticMeshWithEnvironment2(int vCount, int fCount, float *v, float *t, float *n, unsigned short *i) :
m_vertexCount(vCount),
m_indexCount(fCount),
m_vertex(v),
m_texture(t),
m_normals(n),
m_index(i)
{
}

StaticMeshWithEnvironment2::~StaticMeshWithEnvironment2()
{
	delete[] m_vertex;
	delete[] m_texture;
	delete[] m_index;
	delete[] m_normals;
}

void StaticMeshWithEnvironment2::Draw()
{
	glPushMatrix();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_vertex);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, m_normals);

	if (m_textureIndexArray[0])
	{
		glClientActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);			
		glTexCoordPointer(3, GL_FLOAT, 0, m_texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glBindTexture(GL_TEXTURE_2D, m_textureIndexArray[0]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);				
	}
	if (m_textureIndexArray[1])
	{
		glClientActiveTexture(GL_TEXTURE1);
		glActiveTexture(GL_TEXTURE1);
		glEnable(GL_TEXTURE_2D);			
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glBindTexture(GL_TEXTURE_2D, m_textureIndexArray[1]);
		//	setup combiner
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);				
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_REPLACE);
		//	arg0
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_PREVIOUS);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
		//	arg1
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA, GL_TEXTURE);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA);
		//	arg2
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB, GL_PREVIOUS);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_ALPHA, GL_PREVIOUS);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_ALPHA, GL_SRC_ALPHA);
	}

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	if (m_textureIndexArray[0])
	{
		glClientActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE0);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else if (m_textureIndexArray[1])
	{
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	glPopMatrix();

}

void StaticMeshWithEnvironment2::SetTexture(GLuint textureId)
{
	m_textureIndexArray[0] = textureId;
}

void StaticMeshWithEnvironment2::SetEnvironmentMap(GLuint textureId)
{
	m_textureIndexArray[1] = textureId;
}

StaticMeshWithEnvironment2* StaticMeshWithEnvironment2::CreateFromFile(const char *filename)
{
	FILE* f = 0;
	fopen_s(&f, filename, "rb");
	if (f == 0)
		throw std::runtime_error(std::string("Scene::CreateStaticMeshWithEnvironmentMapFromFile: File not found") + filename);
	int vertexCount;
	int faceCount;
	fread(&vertexCount, sizeof(int), 1, f);
	fread(&faceCount, sizeof(int), 1, f);
	float* vertex = new float[vertexCount];
	float* normal = new float[vertexCount];
	float* texture = new float[vertexCount];
	unsigned short* index = new unsigned short[faceCount];
	fread(vertex, sizeof(float), vertexCount, f);
	fread(normal, sizeof(float), vertexCount, f);
	fread(texture, sizeof(float), vertexCount, f);
	fread(index, sizeof(unsigned short), faceCount, f);
	fclose(f);	
	StaticMeshWithEnvironment2* mesh = new StaticMeshWithEnvironment2(vertexCount, faceCount, vertex, texture, normal, index);
	//m_StaticMeshWithEnvironmentMapContainer.push_back(mesh);
	return mesh;

}