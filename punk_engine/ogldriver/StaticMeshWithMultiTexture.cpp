
#include "Os.h"
#include "StaticMeshWithMultiTexture.h"

StaticMeshWithMultiTexture::StaticMeshWithMultiTexture(int vCount, int fCount, float *v, float *t, float *n, unsigned short *i) :
m_vertexCount(vCount),
m_indexCount(fCount),
m_vertex(v),
m_texture(t),
m_normals(n),
m_index(i)
{
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &m_maxTextures);
	m_textureIndexArray = new GLuint[m_maxTextures];
	memset(m_textureIndexArray, 0, sizeof(GLuint)*m_maxTextures);
}

StaticMeshWithMultiTexture::~StaticMeshWithMultiTexture()
{
	delete[] m_vertex;
	delete[] m_texture;
	delete[] m_index;
	delete[] m_normals;
	delete[] m_textureIndexArray;
}

void StaticMeshWithMultiTexture::Draw()
{
	glPushMatrix();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_vertex);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, m_normals);

	for (int i = 0; i < m_maxTextures; i++)
	{
		if (m_textureIndexArray[i])
		{
			glClientActiveTexture(GL_TEXTURE0+i);
			glActiveTexture(GL_TEXTURE0+i);
			glDisable(GL_TEXTURE_3D);
			glDisable(GL_TEXTURE_CUBE_MAP);
			glDisable(GL_REGISTER_COMBINERS_NV);
			glDisable(GL_TEXTURE_SHADER_NV);
			glEnable(GL_TEXTURE_2D);			
			glTexCoordPointer(3, GL_FLOAT, 0, m_texture);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
			glBindTexture(GL_TEXTURE_2D, m_textureIndexArray[i]);
			glGenerateMipmapEXT(GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);				
		}
	}

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	for (int i = 0; i < m_maxTextures; i++)
	{
		glClientActiveTexture(GL_TEXTURE0+i);
		glActiveTexture(GL_TEXTURE0+i);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	glPopMatrix();

}

void StaticMeshWithMultiTexture::SetTexture(int texturePos, GLuint textureId)
{
	m_textureIndexArray[texturePos] = textureId;
}

StaticMeshWithMultiTexture* StaticMeshWithMultiTexture::CreateFromFile(const char *filename)
{
	FILE* f = 0;
	fopen_s(&f, filename, "rb");
	if (f == 0)
		throw std::runtime_error(std::string("Scene::CreateStaticMeshWithMultiTextureFromFile: File not found") + filename);
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
	StaticMeshWithMultiTexture* mesh = new StaticMeshWithMultiTexture(vertexCount, faceCount, vertex, texture, normal, index);
	//m_StaticMeshWithMultiTextureContainer.push_back(mesh);
	return mesh;

}