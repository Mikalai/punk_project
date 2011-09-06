
#include "Os.h"
#include "StaticMeshWith2Textures.h"

StaticMeshWithTexture2::StaticMeshWithTexture2(int vCount, int fCount, float *v, float *t, float *n, unsigned short *i) :
m_vertexCount(vCount),
m_indexCount(fCount),
m_vertex(v),
m_texture(t),
m_normals(n),
m_index(i)
{
	memset(m_color, 0, sizeof(m_color));
	m_color[0] = m_color[1] = m_color[2] = m_color[3] = 1;
}

StaticMeshWithTexture2::~StaticMeshWithTexture2()
{
	delete[] m_vertex;
	delete[] m_texture;
	delete[] m_index;
	delete[] m_normals;
}

void StaticMeshWithTexture2::Draw()
{
	glPushMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
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
		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glLoadIdentity();
		//glScalef(10,10,10);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);				
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
		//	arg0
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
		//	arg1
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_CONSTANT);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
		glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, m_color);/**/
		glMatrixMode(GL_MODELVIEW);
	}
	if (m_textureIndexArray[1])
	{
		glClientActiveTexture(GL_TEXTURE1);
		glActiveTexture(GL_TEXTURE1);
		glEnable(GL_TEXTURE_2D);			
		glTexCoordPointer(3, GL_FLOAT, 0, m_texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glBindTexture(GL_TEXTURE_2D, m_textureIndexArray[1]);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glLoadIdentity();
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);				
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_ADD);
		//	arg0
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
		//	arg1
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
		glMatrixMode(GL_MODELVIEW);
	}

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glClientActiveTexture(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glClientActiveTexture(GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

void StaticMeshWithTexture2::SetTexture(int texturePos, GLuint textureId)
{
	m_textureIndexArray[texturePos] = textureId;
}

void StaticMeshWithTexture2::SetColor(float* color)
{
	memcpy(m_color, color, sizeof(m_color));
}

StaticMeshWithTexture2* StaticMeshWithTexture2::CreateFromFile(const char *filename)
{
	FILE* f = 0;
	fopen_s(&f, filename, "rb");
	if (f == 0)
		throw std::runtime_error(std::string("Scene::CreateStaticMeshWithTexture2FromFile: File not found") + filename);
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
	StaticMeshWithTexture2* mesh = new StaticMeshWithTexture2(vertexCount, faceCount, vertex, texture, normal, index);
	//m_StaticMeshWithTexture2Container.push_back(mesh);
	return mesh;

}