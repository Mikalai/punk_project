
#include "Os.h"
#include "StaticMeshWithTBN.h"

StaticMeshWithTBN::StaticMeshWithTBN(int vCount, int fCount, float *v, float *t, float *n, unsigned short *i) :
m_vertexCount(vCount),
m_indexCount(fCount),
m_vertex(v),
m_texture(t),
m_normals(n),
m_index(i)
{
	//
	//	calculate binormal and tangent
	//
	m_binormal = new float[m_vertexCount];
	m_tangent = new float[m_vertexCount];
	for (int i = 0; i < m_indexCount; i += 3)
	{		
		int a = m_index[i];
		int b = m_index[i+1];
		int c = m_index[i+2];
		float* n1 = &m_normals[3*a];
		float* n2 = &m_normals[3*b];
		float* n3 = &m_normals[3*c];
		float* v1 = &m_vertex[3*a];
		float* v2 = &m_vertex[3*b];
		float* v3 = &m_vertex[3*c];
		float* t1 = &m_tangent[3*a];
		float* t2 = &m_tangent[3*b];
		float* t3 = &m_tangent[3*c];
		float* b1 = &m_binormal[3*a];
		float* b2 = &m_binormal[3*b];
		float* b3 = &m_binormal[3*c];
		if (i%2==0)
			Math::glNormalize3fv(t1, Math::glSubVector3fv(t1, v2, v1));	
		else
			Math::glNormalize3fv(t1, Math::glSubVector3fv(t1, v1, v2));	
		Math::glNormalize3fv(b1, Math::glCrossProduct3fv(b1, n1, t1));
		if (i%2==0)
			Math::glNormalize3fv(t2, Math::glSubVector3fv(t2, v2, v3));		
		else
			Math::glNormalize3fv(t2, Math::glSubVector3fv(t2, v3, v2));		
		Math::glNormalize3fv(b2, Math::glCrossProduct3fv(b2, n2, t2));	
		if (i%2)
			Math::glNormalize3fv(t3, Math::glSubVector3fv(t3, v3, v1));		
		else
			Math::glNormalize3fv(t3, Math::glSubVector3fv(t3, v1, v3));		
		Math::glNormalize3fv(b3, Math::glCrossProduct3fv(b3, n3, t3));	

	}
	m_lightPos[0] = 0;
	m_lightPos[1] = 1;
	m_lightPos[2] = 1;
	
	m_lightVector = new float[m_vertexCount];
	for (int i = 0; i < m_vertexCount; i += 3)
	{
		float* n = &m_normals[i];
		float* b = &m_binormal[i];
		float* t = &m_tangent[i];
		float v[3];
		Math::glSetVector3fv(v, Math::glSubVector3fv(v, m_lightPos, &m_vertex[i]));
		m_lightVector[i+0] = Math::glDotProduct3fv(v, t);
		m_lightVector[i+1] = Math::glDotProduct3fv(v, b);
		m_lightVector[i+2] = Math::glDotProduct3fv(v, n);

		float temp[3];
		temp[0] = Math::glDotProduct3fv(n, t);
		temp[1] = Math::glDotProduct3fv(n, b);
		temp[2] = Math::glDotProduct3fv(n, n);

		Math::glNormalize3fv(&m_lightVector[i], &m_lightVector[i]);
	}
}

StaticMeshWithTBN::~StaticMeshWithTBN()
{
	delete[] m_vertex;
	delete[] m_texture;
	delete[] m_index;
	delete[] m_normals;
	delete[] m_lightVector;
	delete[] m_binormal;
	delete[] m_tangent;
}

void StaticMeshWithTBN::Draw()
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
	if (m_decal)
	{
		glClientActiveTexture(GL_TEXTURE2);
		glActiveTexture(GL_TEXTURE2);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_CUBE_MAP);
		glTexCoordPointer(3, GL_FLOAT, 0, m_texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, m_decal);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_PREVIOUS);
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
	}

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glClientActiveTexture(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
	glClientActiveTexture(GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
	glClientActiveTexture(GL_TEXTURE2);
	glActiveTexture(GL_TEXTURE2);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
	glPopMatrix();

}

void StaticMeshWithTBN::SetNormalizationMap(GLuint textureId)
{
	m_normalizationCubeMap = textureId;
}

void StaticMeshWithTBN::SetBumpMap(GLuint textureId)
{
	m_bumpMap = textureId;
}

void StaticMeshWithTBN::SetDecal(GLuint textureId)
{
	m_decal = textureId;
}

void StaticMeshWithTBN::SetLightPos(float x, float y, float z)
{
	m_lightPos[0] = x; m_lightPos[1] = y; m_lightPos[2] = z;
	for (int i = 0; i < m_vertexCount; i += 3)
	{
		float* n = &m_normals[i];
		float* b = &m_binormal[i];
		float* t = &m_tangent[i];
		float v[3];
//		if (i%2==0)
		Math::glNormalize3fv(v, Math::glSubVector3fv(v, m_lightPos, &m_vertex[i]));
//		else
//			Math::glSetVector3fv(v, Math::glSubVector3fv(v, &m_vertex[i], m_lightPos));
		m_lightVector[i+0] = Math::glDotProduct3fv(v, t);
		m_lightVector[i+1] = Math::glDotProduct3fv(v, b);
		m_lightVector[i+2] = Math::glDotProduct3fv(v, n);
		Math::glNormalize3fv(&m_lightVector[i], &m_lightVector[i]);
	}
}

StaticMeshWithTBN* StaticMeshWithTBN::CreateFromFile(const char *filename)
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
	StaticMeshWithTBN* mesh = new StaticMeshWithTBN(vertexCount, faceCount, vertex, texture, normal, index);
	//m_StaticMeshWithMultiTextureContainer.push_back(mesh);
	return mesh;

}