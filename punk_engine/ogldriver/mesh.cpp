
#include <stdio.h>
#include "../Util/Util.h"
#include "Mesh.h"
#include "Texture2D.h"

TMesh::TMesh() : m_useBlending(false), m_childCount(0), m_parent(NULL), m_child(NULL),
m_texture(NULL)
{
	memset(m_transform, 0, sizeof(m_transform));
	m_transform[0] = m_transform[5] = m_transform[10] = m_transform[15] = 1.0f;
#ifdef _DEBUG
	printf("TMesh()\n");
#endif
}

TMesh::~TMesh()
{
#ifdef _DEBUG
	printf("~TMesh()\n");
#endif
}

bool TMesh::LoadMesh(const Char *filename)
{
	FILE* f = 0;
	_tfopen_s(&f, filename, PUNK_TEXT("rt"));
	if (f == 0)
		return false;
	char* buffer = new char[PUNK_MAX_SMALL_BUFFER_SIZE];
	try
	{
		fscanf_s(f, "%d", &m_type);
		fscanf_s(f, "%s", buffer, PUNK_MAX_SMALL_BUFFER_SIZE);
		m_name = buffer;
		if (m_type & PUNK_EXPORT_MATERIAL)
		{
			fscanf_s(f, "%f%f%f", m_material.m_ambient, m_material.m_ambient+1, m_material.m_diffuse+2);
			fscanf_s(f, "%f%f%f", m_material.m_diffuse, m_material.m_diffuse+1, m_material.m_diffuse+2);
			fscanf_s(f, "%f%f%f", m_material.m_specular, m_material.m_specular+1, m_material.m_specular+2);
			fscanf_s(f, "%f", &m_material.m_shine);
			fscanf_s(f, "%f", &m_material.m_shineStrength);
			fscanf_s(f, "%f", &m_material.m_transparency);
			m_material.m_diffuse[3] = m_material.m_ambient[3] = 1 - m_material.m_transparency;

			fscanf_s(f, "%d", &m_material.m_subMaterialCount);
			if (m_material.m_subMaterialCount != 0)
			{
				m_material.m_subMaterial = new TMaterial[m_material.m_subMaterialCount];
				try
				{
					for (int i = 0; i < m_material.m_subMaterialCount; i++)
					{
						fscanf_s(f, "%f%f%f", m_material.m_subMaterial[i].m_ambient, m_material.m_subMaterial[i].m_ambient+1, m_material.m_subMaterial[i].m_diffuse+2);
						fscanf_s(f, "%f%f%f", m_material.m_subMaterial[i].m_diffuse, m_material.m_subMaterial[i].m_diffuse+1, m_material.m_subMaterial[i].m_diffuse+2);
						fscanf_s(f, "%f%f%f", m_material.m_subMaterial[i].m_specular, m_material.m_subMaterial[i].m_specular+1, m_material.m_subMaterial[i].m_specular+2);
						fscanf_s(f, "%f", &m_material.m_subMaterial[i].m_shine);
						fscanf_s(f, "%f", &m_material.m_subMaterial[i].m_shineStrength);
						fscanf_s(f, "%f", &m_material.m_subMaterial[i].m_transparency);					
					}
				}
				catch(...)
				{
					DELETE_ARRAY(m_material.m_subMaterial);
					throw;
				}
			}
		}

		if (m_type & PUNK_EXPORT_POSITION)
		{
			fscanf_s(f, "%d", &m_data.m_vertexCount);
			m_data.m_vertexPosition = new VertexPosition[m_data.m_vertexCount];
			try
			{
				for (int i = 0; i < m_data.m_vertexCount; i++)
				{
					fscanf_s(f, "%f%f%f", 
						&m_data.m_vertexPosition[i][0], 
						&m_data.m_vertexPosition[i][1], 
						&m_data.m_vertexPosition[i][2]);
				}
			}
			catch(...)
			{
				DELETE_ARRAY(m_data.m_vertexPosition);
				m_data.m_vertexPosition = NULL;
				throw;
			}		
		}

		//
		//	normals
		//
		if (m_type & PUNK_EXPORT_NORMAL)
		{
			fscanf_s(f, "%d", &m_data.m_normalsCount);
			m_data.m_vertexNormal = new VertexNormal[m_data.m_normalsCount];
			try
			{
				for (int i = 0; i < m_data.m_normalsCount; i++)
				{
					fscanf_s(f, "%f%f%f",
						&m_data.m_vertexNormal[i][0],
						&m_data.m_vertexNormal[i][1], 
						&m_data.m_vertexNormal[i][2]);
				}
			}
			catch(...)
			{
				DELETE_ARRAY(m_data.m_vertexNormal);
				m_data.m_vertexNormal = NULL;
				throw;
			}			
		}

		//
		//	texcoord
		//
		if (m_type & PUNK_EXPORT_TEXCOORD)
		{
			m_data.m_vertexTexcoord = new VertexTexcoord[m_data.m_vertexCount];
			try
			{
				for (int i = 0; i < m_data.m_vertexCount; i++)
				{
					fscanf_s(f, "%f%f%f", 
						&m_data.m_vertexTexcoord[i][0],
						&m_data.m_vertexTexcoord[i][1], 
						&m_data.m_vertexTexcoord[i][2]);
				}
			}
			catch(...)
			{
				DELETE_ARRAY(m_data.m_vertexTexcoord);
				m_data.m_vertexTexcoord = NULL;
				throw;
			}
		}

		//
		//	face description
		//
		fscanf_s(f, "%d", &m_data.m_faceCount);
		m_data.m_face = new Face[m_data.m_faceCount];
		for (int i = 0; i < m_data.m_faceCount; i++)
		{
			fscanf_s(f, "%d%d%d", &m_data.m_face[i][0],
				&m_data.m_face[i][1],
				&m_data.m_face[i][2]);
		}

		DELETE_ARRAY(buffer);
	}
	catch(...)
	{
		DELETE_ARRAY(buffer);
		throw;
	}
	fclose(f);


	//
	//	opengl must know what to draw
	//
	return true;
}

bool TMesh::LoadPunkMesh_v_0_1(const Char *filename)
{
	return false;
}

void TMesh::UseBlending(bool use)
{
	m_useBlending = use;
}

bool TMesh::Render()
{
	glPushMatrix();
	glMultMatrixf(m_transform);
	if (m_texture)
	{
		//m_texture->Apply();
	}

	if (m_useBlending)
	{
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_material.Apply();
				
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, m_data.m_vertexPosition);
		glNormalPointer(GL_FLOAT, 0, m_data.m_vertexNormal);
		glTexCoordPointer(3, GL_FLOAT, 0, m_data.m_vertexTexcoord);
		glDrawElements(GL_TRIANGLES, m_data.m_faceCount*3, GL_UNSIGNED_INT, m_data.m_face);/**/
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);/**/
	}
	else
	{
		m_material.Apply();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		if (m_data.m_vertexTexcoord)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, m_data.m_vertexPosition);
		glNormalPointer(GL_FLOAT, 0, m_data.m_vertexNormal);
		if (m_data.m_vertexTexcoord)
			glTexCoordPointer(3, GL_FLOAT, 0, m_data.m_vertexTexcoord);
		glDrawElements(GL_TRIANGLES, 3*m_data.m_faceCount, GL_UNSIGNED_INT, m_data.m_face);/**/
		glDisableClientState(GL_VERTEX_ARRAY);
		if (m_data.m_vertexTexcoord)
			glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glFlush();/**/
	}
	glPopMatrix();
	return true;
}

bool TMesh::SetWorldTransform(void *transform)
{
	memcpy(m_transform, transform, sizeof(m_transform));
	//throw Exception("TMesh::SetWorldTransofrm not emplemented");
	return false;
}

bool TMesh::AttachChild(TMesh *mesh)
{
	throw Exception("TMesh::AttachChild not implemented");
	return false;
}

bool TMesh::DetachChild(TMesh *mesh)
{
	throw Exception("TMesh::DetachChild not implemented");
	return false;
}

TMesh** TMesh::GetChildren()
{
	throw Exception("TMesh::GetChild not implemented");
	return 0;
}

int TMesh::GetChildrenCount() const
{
	throw Exception("TMesh::GetChildren not implemented");
	return 0;
}

const PunkString& TMesh::GetName() const
{
	return m_name;
}

TMesh::MeshData::MeshData() : m_vertexCount(0), m_faceCount(0), m_normalsCount(0),
m_vertexPosition(NULL), m_face(NULL), m_vertexNormal(NULL), m_vertexTexcoord(NULL),
m_faceNormal(NULL)
{
#ifdef _DEBUG
	printf("TMesh::MeshData()\n");
#endif
}

TMesh::MeshData::~MeshData()
{
#ifdef _DEBUG
	printf("~TMesh::MeshData()\n");
#endif
	DELETE_ARRAY(m_vertexPosition);
	DELETE_ARRAY(m_face);
	DELETE_ARRAY(m_vertexNormal);
	DELETE_ARRAY(m_vertexTexcoord);
	DELETE_ARRAY(m_faceNormal);
}

void TMesh::ApplyTexture(ITexture2D *texture)
{
	m_texture = (TTexture2D*)texture;
}

void* TMesh::GetVertex()
{
	return m_data.m_vertexPosition;
}

int TMesh::GetVertexCount() const
{
	return m_data.m_vertexCount;
}

int TMesh::GetTrianglesCount() const
{
	return m_data.m_faceCount;
}

void* TMesh::GetTriangles()
{
	return m_data.m_face;
}
#include <stdio.h>
#include "../Util/Util.h"
#include "Mesh.h"
#include "Texture2D.h"

TMesh::TMesh() : m_useBlending(false), m_childCount(0), m_parent(NULL), m_child(NULL),
m_texture(NULL)
{
	memset(m_transform, 0, sizeof(m_transform));
	m_transform[0] = m_transform[5] = m_transform[10] = m_transform[15] = 1.0f;
#ifdef _DEBUG
	printf("TMesh()\n");
#endif
}

TMesh::~TMesh()
{
#ifdef _DEBUG
	printf("~TMesh()\n");
#endif
}

bool TMesh::LoadMesh(const Char *filename)
{
	FILE* f = 0;
	_tfopen_s(&f, filename, PUNK_TEXT("rt"));
	if (f == 0)
		return false;
	char* buffer = new char[PUNK_MAX_SMALL_BUFFER_SIZE];
	try
	{
		fscanf_s(f, "%d", &m_type);
		fscanf_s(f, "%s", buffer, PUNK_MAX_SMALL_BUFFER_SIZE);
		m_name = buffer;
		if (m_type & PUNK_EXPORT_MATERIAL)
		{
			fscanf_s(f, "%f%f%f", m_material.m_ambient, m_material.m_ambient+1, m_material.m_diffuse+2);
			fscanf_s(f, "%f%f%f", m_material.m_diffuse, m_material.m_diffuse+1, m_material.m_diffuse+2);
			fscanf_s(f, "%f%f%f", m_material.m_specular, m_material.m_specular+1, m_material.m_specular+2);
			fscanf_s(f, "%f", &m_material.m_shine);
			fscanf_s(f, "%f", &m_material.m_shineStrength);
			fscanf_s(f, "%f", &m_material.m_transparency);
			m_material.m_diffuse[3] = m_material.m_ambient[3] = 1 - m_material.m_transparency;

			fscanf_s(f, "%d", &m_material.m_subMaterialCount);
			if (m_material.m_subMaterialCount != 0)
			{
				m_material.m_subMaterial = new TMaterial[m_material.m_subMaterialCount];
				try
				{
					for (int i = 0; i < m_material.m_subMaterialCount; i++)
					{
						fscanf_s(f, "%f%f%f", m_material.m_subMaterial[i].m_ambient, m_material.m_subMaterial[i].m_ambient+1, m_material.m_subMaterial[i].m_diffuse+2);
						fscanf_s(f, "%f%f%f", m_material.m_subMaterial[i].m_diffuse, m_material.m_subMaterial[i].m_diffuse+1, m_material.m_subMaterial[i].m_diffuse+2);
						fscanf_s(f, "%f%f%f", m_material.m_subMaterial[i].m_specular, m_material.m_subMaterial[i].m_specular+1, m_material.m_subMaterial[i].m_specular+2);
						fscanf_s(f, "%f", &m_material.m_subMaterial[i].m_shine);
						fscanf_s(f, "%f", &m_material.m_subMaterial[i].m_shineStrength);
						fscanf_s(f, "%f", &m_material.m_subMaterial[i].m_transparency);					
					}
				}
				catch(...)
				{
					DELETE_ARRAY(m_material.m_subMaterial);
					throw;
				}
			}
		}

		if (m_type & PUNK_EXPORT_POSITION)
		{
			fscanf_s(f, "%d", &m_data.m_vertexCount);
			m_data.m_vertexPosition = new VertexPosition[m_data.m_vertexCount];
			try
			{
				for (int i = 0; i < m_data.m_vertexCount; i++)
				{
					fscanf_s(f, "%f%f%f", 
						&m_data.m_vertexPosition[i][0], 
						&m_data.m_vertexPosition[i][1], 
						&m_data.m_vertexPosition[i][2]);
				}
			}
			catch(...)
			{
				DELETE_ARRAY(m_data.m_vertexPosition);
				m_data.m_vertexPosition = NULL;
				throw;
			}		
		}

		//
		//	normals
		//
		if (m_type & PUNK_EXPORT_NORMAL)
		{
			fscanf_s(f, "%d", &m_data.m_normalsCount);
			m_data.m_vertexNormal = new VertexNormal[m_data.m_normalsCount];
			try
			{
				for (int i = 0; i < m_data.m_normalsCount; i++)
				{
					fscanf_s(f, "%f%f%f",
						&m_data.m_vertexNormal[i][0],
						&m_data.m_vertexNormal[i][1], 
						&m_data.m_vertexNormal[i][2]);
				}
			}
			catch(...)
			{
				DELETE_ARRAY(m_data.m_vertexNormal);
				m_data.m_vertexNormal = NULL;
				throw;
			}			
		}

		//
		//	texcoord
		//
		if (m_type & PUNK_EXPORT_TEXCOORD)
		{
			m_data.m_vertexTexcoord = new VertexTexcoord[m_data.m_vertexCount];
			try
			{
				for (int i = 0; i < m_data.m_vertexCount; i++)
				{
					fscanf_s(f, "%f%f%f", 
						&m_data.m_vertexTexcoord[i][0],
						&m_data.m_vertexTexcoord[i][1], 
						&m_data.m_vertexTexcoord[i][2]);
				}
			}
			catch(...)
			{
				DELETE_ARRAY(m_data.m_vertexTexcoord);
				m_data.m_vertexTexcoord = NULL;
				throw;
			}
		}

		//
		//	face description
		//
		fscanf_s(f, "%d", &m_data.m_faceCount);
		m_data.m_face = new Face[m_data.m_faceCount];
		for (int i = 0; i < m_data.m_faceCount; i++)
		{
			fscanf_s(f, "%d%d%d", &m_data.m_face[i][0],
				&m_data.m_face[i][1],
				&m_data.m_face[i][2]);
		}

		DELETE_ARRAY(buffer);
	}
	catch(...)
	{
		DELETE_ARRAY(buffer);
		throw;
	}
	fclose(f);


	//
	//	opengl must know what to draw
	//
	return true;
}

bool TMesh::LoadPunkMesh_v_0_1(const Char *filename)
{
	return false;
}

void TMesh::UseBlending(bool use)
{
	m_useBlending = use;
}

bool TMesh::Render()
{
	glPushMatrix();
	glMultMatrixf(m_transform);
	if (m_texture)
	{
		//m_texture->Apply();
	}

	if (m_useBlending)
	{
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_material.Apply();
				
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, m_data.m_vertexPosition);
		glNormalPointer(GL_FLOAT, 0, m_data.m_vertexNormal);
		glTexCoordPointer(3, GL_FLOAT, 0, m_data.m_vertexTexcoord);
		glDrawElements(GL_TRIANGLES, m_data.m_faceCount*3, GL_UNSIGNED_INT, m_data.m_face);/**/
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);/**/
	}
	else
	{
		m_material.Apply();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		if (m_data.m_vertexTexcoord)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, m_data.m_vertexPosition);
		glNormalPointer(GL_FLOAT, 0, m_data.m_vertexNormal);
		if (m_data.m_vertexTexcoord)
			glTexCoordPointer(3, GL_FLOAT, 0, m_data.m_vertexTexcoord);
		glDrawElements(GL_TRIANGLES, 3*m_data.m_faceCount, GL_UNSIGNED_INT, m_data.m_face);/**/
		glDisableClientState(GL_VERTEX_ARRAY);
		if (m_data.m_vertexTexcoord)
			glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glFlush();/**/
	}
	glPopMatrix();
	return true;
}

bool TMesh::SetWorldTransform(void *transform)
{
	memcpy(m_transform, transform, sizeof(m_transform));
	//throw Exception("TMesh::SetWorldTransofrm not emplemented");
	return false;
}

bool TMesh::AttachChild(TMesh *mesh)
{
	throw Exception("TMesh::AttachChild not implemented");
	return false;
}

bool TMesh::DetachChild(TMesh *mesh)
{
	throw Exception("TMesh::DetachChild not implemented");
	return false;
}

TMesh** TMesh::GetChildren()
{
	throw Exception("TMesh::GetChild not implemented");
	return 0;
}

int TMesh::GetChildrenCount() const
{
	throw Exception("TMesh::GetChildren not implemented");
	return 0;
}

const PunkString& TMesh::GetName() const
{
	return m_name;
}

TMesh::MeshData::MeshData() : m_vertexCount(0), m_faceCount(0), m_normalsCount(0),
m_vertexPosition(NULL), m_face(NULL), m_vertexNormal(NULL), m_vertexTexcoord(NULL),
m_faceNormal(NULL)
{
#ifdef _DEBUG
	printf("TMesh::MeshData()\n");
#endif
}

TMesh::MeshData::~MeshData()
{
#ifdef _DEBUG
	printf("~TMesh::MeshData()\n");
#endif
	DELETE_ARRAY(m_vertexPosition);
	DELETE_ARRAY(m_face);
	DELETE_ARRAY(m_vertexNormal);
	DELETE_ARRAY(m_vertexTexcoord);
	DELETE_ARRAY(m_faceNormal);
}

void TMesh::ApplyTexture(ITexture2D *texture)
{
	m_texture = (TTexture2D*)texture;
}

void* TMesh::GetVertex()
{
	return m_data.m_vertexPosition;
}

int TMesh::GetVertexCount() const
{
	return m_data.m_vertexCount;
}

int TMesh::GetTrianglesCount() const
{
	return m_data.m_faceCount;
}

void* TMesh::GetTriangles()
{
	return m_data.m_face;
}