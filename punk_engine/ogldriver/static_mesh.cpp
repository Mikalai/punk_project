
#include "Os.h"
#include "StaticMesh.h"

StaticMesh::StaticMesh(int vCount, int fCount, float *v, float *t, float *n, unsigned short *i) :
m_vertexCount(vCount),
m_indexCount(fCount),
m_vertex(v),
m_texture(t),
m_normals(n),
m_index(i)
{}

StaticMesh::~StaticMesh()
{
	delete[] m_vertex;
	delete[] m_texture;
	delete[] m_index;
	delete[] m_normals;
}

void StaticMesh::Draw()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, m_vertex);
	glNormalPointer(GL_FLOAT, 0, m_normals);
	glTexCoordPointer(3, GL_FLOAT, 0, m_texture);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

StaticMesh* StaticMesh::CreateFromFile(const char *filename)
{
	FILE* f = 0;
	fopen_s(&f, filename, "rb");
	if (f == 0)
		throw std::runtime_error(std::string("Scene::CreateStaticMeshFromFile: File not found") + filename);
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
	StaticMesh* mesh = new StaticMesh(vertexCount, faceCount, vertex, texture, normal, index);
	//m_staticMeshContainer.push_back(mesh);
	return mesh;

}