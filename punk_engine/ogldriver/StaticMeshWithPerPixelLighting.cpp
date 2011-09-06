
#include "Os.h"
#include "StaticMeshWithPerPixelLighting.h"

StaticMeshWithPerPixelLighting::StaticMeshWithPerPixelLighting(int vCount, int fCount, float *v, float *t, float *n, unsigned short *i) :
m_vertexCount(vCount),
m_indexCount(fCount),
m_vertex(v),
m_texture(t),
m_normals(n),
m_index(i)
{
	m_lightPos[0] = 0;
	m_lightPos[1] = 1;
	m_lightPos[2] = 1;
	
	m_lightVector = new float[m_vertexCount];
	for (int i = 0; i < m_vertexCount; i += 3)
	{
		m_lightVector[i+0] = m_lightPos[0] - m_vertex[i+0];
		m_lightVector[i+1] = m_lightPos[1] - m_vertex[i+1];
		m_lightVector[i+2] = m_lightPos[2] - m_vertex[i+2];

		float c = sqrt(m_lightVector[i+0]*m_lightVector[i+0]+
			m_lightVector[i+1]*m_lightVector[i+1]+
			m_lightVector[i+2]*m_lightVector[i+2]);
		m_lightVector[i+0] /= c;
		m_lightVector[i+1] /= c;
		m_lightVector[i+2] /= c;
	}
}

StaticMeshWithPerPixelLighting::~StaticMeshWithPerPixelLighting()
{
	delete[] m_vertex;
	delete[] m_texture;
	delete[] m_index;
	delete[] m_normals;
	delete[] m_lightVector;
}

void StaticMeshWithPerPixelLighting::Draw()
{
	glPushMatrix();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_vertex);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, m_normals);

	if (m_bumpMap)
	{
		glClientActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_bumpMap);
		glTexCoordPointer(3, GL_FLOAT, 0, m_texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);
	}
	if (m_normalizationCubeMap)
	{
		glClientActiveTexture(GL_TEXTURE1);
		glActiveTexture(GL_TEXTURE1);
		glEnable(GL_TEXTURE_CUBE_MAP);		
		glTexCoordPointer(3, GL_FLOAT, 0, m_lightVector);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_normalizationCubeMap);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_PREVIOUS);
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_DOT3_RGB);
	}/**/

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glClientActiveTexture(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
	glClientActiveTexture(GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	

	glPopMatrix();

}

void StaticMeshWithPerPixelLighting::SetNormalizationMap(GLuint textureId)
{
	m_normalizationCubeMap = textureId;
}

void StaticMeshWithPerPixelLighting::SetBumpMap(GLuint textureId)
{
	m_bumpMap = textureId;
}

void StaticMeshWithPerPixelLighting::SetLightPos(float x, float y, float z)
{
	m_lightPos[0] = x; m_lightPos[1] = y; m_lightPos[2] = z;
	for (int i = 0; i < m_vertexCount; i += 3)
	{
		m_lightVector[i+0] = m_lightPos[0] - m_vertex[i+0];
		m_lightVector[i+1] = m_lightPos[1] - m_vertex[i+1];
		m_lightVector[i+2] = m_lightPos[2] - m_vertex[i+2];

		float c = sqrt(m_lightVector[i+0]*m_lightVector[i+0]+
			m_lightVector[i+1]*m_lightVector[i+1]+
			m_lightVector[i+2]*m_lightVector[i+2]);
		m_lightVector[i+0] /= c;
		m_lightVector[i+1] /= c;
		m_lightVector[i+2] /= c;
	}
}

StaticMeshWithPerPixelLighting* StaticMeshWithPerPixelLighting::CreateFromFile(const char *filename)
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
	StaticMeshWithPerPixelLighting* mesh = new StaticMeshWithPerPixelLighting(vertexCount, faceCount, vertex, texture, normal, index);
	//m_StaticMeshWithMultiTextureContainer.push_back(mesh);
	return mesh;

}