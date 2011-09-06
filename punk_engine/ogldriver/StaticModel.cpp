#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#endif

#include <GL/wglext.h>
#include <GL/glext.h>

#include "StaticModel.h"
#include "Driver.h"

StaticModel::StaticModel(StaticMesh *mesh) : m_mesh(mesh), m_maxTextures(g_driver->GetMaxTextureUnits())
{
	memset(m_transform, 0, sizeof(m_transform));
	m_transform[0] = m_transform[5] = m_transform[10] = m_transform[15] = 1.0f;
	m_textures = new unsigned[m_maxTextures];
	memset(m_textures, 0, sizeof(TTexture2D)*m_maxTextures);
}

void StaticModel::Draw()
{
	InternalDraw_v1();
}

void StaticModel::InternalDraw_v1()
{
	glPushMatrix();
	glMultMatrixf(m_transform);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_mesh->m_vertex);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, m_mesh->m_normals);

	for (int i = 0; i < m_maxTextures; i++)
	{
		glClientActiveTextureARB(GL_TEXTURE0_ARB+i);
		glActiveTextureARB(GL_TEXTURE0_ARB+i);
		glEnable(GL_TEXTURE_2D);			
		if (i == m_envMapID)
		{
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
			glBindTexture(GL_TEXTURE_2D, m_textures[1]);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		}
		else
		{
			glTexCoordPointer(3, GL_FLOAT, 0, m_mesh->m_texture);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
			glBindTexture(GL_TEXTURE_2D, m_textures[0]);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);				
		}

	}
	glDrawElements(GL_TRIANGLES, m_mesh->m_indexCount, GL_UNSIGNED_SHORT, m_mesh->m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	for (int i = 0; i < m_maxTextures; i++)
	{
		glClientActiveTextureARB(GL_TEXTURE0_ARB+i);
		glActiveTextureARB(GL_TEXTURE0_ARB+i);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	glPopMatrix();
}

void StaticModel::InternalDraw_v2()
{
	glPushMatrix();
	glMultMatrixf(m_transform);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_mesh->m_vertex);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, m_mesh->m_normals);

	glDrawElements(GL_TRIANGLES, m_mesh->m_indexCount, GL_UNSIGNED_SHORT, m_mesh->m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glPopMatrix();
}
void StaticModel::SetTransform(float* transform)
{
	memcpy(m_transform, transform, sizeof(m_transform));
}

void StaticModel::SetPosition(float x, float y, float z)
{
	m_transform[12] = x;
	m_transform[13] = y;
	m_transform[14] = z;
}

void StaticModel::SetTexture(unsigned int id, unsigned name)
{
	m_textures[id] = name;
}

void StaticModel::SetEnvironmentMap(unsigned int id, unsigned int texture)
{
	m_envMapID = id;
	m_textures[id] = texture;
}#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#endif

#include <GL/wglext.h>
#include <GL/glext.h>

#include "StaticModel.h"
#include "Driver.h"

StaticModel::StaticModel(StaticMesh *mesh) : m_mesh(mesh), m_maxTextures(g_driver->GetMaxTextureUnits())
{
	memset(m_transform, 0, sizeof(m_transform));
	m_transform[0] = m_transform[5] = m_transform[10] = m_transform[15] = 1.0f;
	m_textures = new unsigned[m_maxTextures];
	memset(m_textures, 0, sizeof(TTexture2D)*m_maxTextures);
}

void StaticModel::Draw()
{
	InternalDraw_v1();
}

void StaticModel::InternalDraw_v1()
{
	glPushMatrix();
	glMultMatrixf(m_transform);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_mesh->m_vertex);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, m_mesh->m_normals);

	for (int i = 0; i < m_maxTextures; i++)
	{
		glClientActiveTextureARB(GL_TEXTURE0_ARB+i);
		glActiveTextureARB(GL_TEXTURE0_ARB+i);
		glEnable(GL_TEXTURE_2D);			
		if (i == m_envMapID)
		{
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
			glBindTexture(GL_TEXTURE_2D, m_textures[1]);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		}
		else
		{
			glTexCoordPointer(3, GL_FLOAT, 0, m_mesh->m_texture);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
			glBindTexture(GL_TEXTURE_2D, m_textures[0]);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);				
		}

	}
	glDrawElements(GL_TRIANGLES, m_mesh->m_indexCount, GL_UNSIGNED_SHORT, m_mesh->m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	for (int i = 0; i < m_maxTextures; i++)
	{
		glClientActiveTextureARB(GL_TEXTURE0_ARB+i);
		glActiveTextureARB(GL_TEXTURE0_ARB+i);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	glPopMatrix();
}

void StaticModel::InternalDraw_v2()
{
	glPushMatrix();
	glMultMatrixf(m_transform);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_mesh->m_vertex);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, m_mesh->m_normals);

	glDrawElements(GL_TRIANGLES, m_mesh->m_indexCount, GL_UNSIGNED_SHORT, m_mesh->m_index);/**/

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glPopMatrix();
}
void StaticModel::SetTransform(float* transform)
{
	memcpy(m_transform, transform, sizeof(m_transform));
}

void StaticModel::SetPosition(float x, float y, float z)
{
	m_transform[12] = x;
	m_transform[13] = y;
	m_transform[14] = z;
}

void StaticModel::SetTexture(unsigned int id, unsigned name)
{
	m_textures[id] = name;
}

void StaticModel::SetEnvironmentMap(unsigned int id, unsigned int texture)
{
	m_envMapID = id;
	m_textures[id] = texture;
}