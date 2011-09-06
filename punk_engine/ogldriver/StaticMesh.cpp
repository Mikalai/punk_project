#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

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