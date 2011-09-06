#include "Terrain.h"
#include <math.h>
#include "../Util/Image.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glext.h>
#include "Texture2D.h"
#include "Driver.h"

Terrain::Terrain() : m_maxTextures(g_driver->GetMaxTextureUnits())
{
	m_zoom[0] = 0.1f;
	m_zoom[1] = 0.1f;
	m_zoom[2] = 2;
	memset(m_transform, 0, sizeof(m_transform));
	m_transform[0] = m_transform[5] = m_transform[10] = m_transform[15] = 1.0f;
	m_textures = new unsigned[m_maxTextures];
	memset(m_textures, 0, sizeof(TTexture2D)*m_maxTextures);
	m_envMapID = -1;
}

Terrain::~Terrain()
{
}

void Terrain::Draw()
{
	InternalDraw_v3();
}

//
//	use texture combiner for microrelief
//	0 - main texture
//	1 - detail texture
//
void Terrain::InternalDraw_v3()
{
	glPushMatrix();
	//glLoadIdentity();
	glMultMatrixf(m_transform);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_vertex);
	glEnableClientState(GL_NORMAL_ARRAY);	
	glNormalPointer(GL_FLOAT, 0, m_normals);
	
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);			
	glTexCoordPointer(2, GL_FLOAT, 0, m_texture);
	glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_REPLACE);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glTexCoordPointer(2, GL_FLOAT, 0, m_texture);
	glBindTexture(GL_TEXTURE_2D, m_textures[1]);
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glScalef(30, 30, 30);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);
	//	arg0
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR);
	//	arg1
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR);
	
	glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);/**/

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, m_index);/**/
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	for (int i = 0; i < m_maxTextures; i++)
	{
		glClientActiveTextureARB(GL_TEXTURE0_ARB+i);
		glActiveTextureARB(GL_TEXTURE0_ARB+i);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}/**/	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();/**/
}

//
//	use texture and pointers
//
void Terrain::InternalDraw_v1()
{
	glPushMatrix();
	//glLoadIdentity();
	glMultMatrixf(m_transform);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_vertex);
	glNormalPointer(GL_FLOAT, 0, m_normals);

	for (int i = 0; i < m_maxTextures; i++)
	{	
		if (m_textures[i])
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
				glBindTexture(GL_TEXTURE_2D, m_textures[i]);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
			}
			else
			{
				glMatrixMode(GL_TEXTURE);
				glLoadIdentity();
				glScalef(30,30,30);
				glTexCoordPointer(2, GL_FLOAT, 0, m_texture);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
				glBindTexture(GL_TEXTURE_2D, m_textures[i]);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);				
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
			}
		}

	}/**/
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, m_index);/**/

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

void Terrain::InternalDraw_v2()
{
	for (int i = 0; i < m_indexCount / 3; i += 3)
	{
		glBegin(GL_TRIANGLES);
		glVertex3fv(&m_vertex[m_index[i+0]]);
		glVertex3fv(&m_vertex[m_index[i+1]]);
		glVertex3fv(&m_vertex[m_index[i+2]]);
		glEnd();
	}
}

void Terrain::SetZoom(float zoom[])
{
	memcpy(m_zoom, zoom, sizeof(m_zoom));;
}

void Terrain::Update(float delta)
{
}

void Terrain::GenerateFromHeightMap(const Image* image)
{
	float height = 0;
	int step = sizeof(char)*image->m_bitsPerPixel/8;
	m_vertexCount = (image->m_width+1)*(image->m_height+1);
	m_indexCount = (image->m_width-1)*(image->m_height-1)*2*3;
	m_vertex = new float[m_vertexCount*sizeof(float)*3];
	m_normals = new float[m_vertexCount*sizeof(float)*3];
	memset(m_normals, 0, sizeof(float)*3*m_vertexCount);
	m_texture = new float[m_vertexCount*sizeof(float)*2];
	m_index = new unsigned[m_indexCount];
	float max[3] = {-1e+32, -1e+32, -1e+32};
	float min[3] = {1e+32, 1e+32, 1e+32};
	for (int i = 0; i < image->m_height; i++)
	{
		for (int j = 0; j < image->m_width; j++)
		{
			float height;
			if (image->m_bitsPerPixel>>3 == 1)
			{
				height = image->m_data[i*image->m_width+j];
			}
			else if (image->m_bitsPerPixel>>3 == 3)
			{
				height = (image->m_data[i*image->m_width*step+j*step + 0]+
					image->m_data[i*image->m_width*step+j*step + 1]+
					image->m_data[i*image->m_width*step+j*step + 2])/3;
			}
			else
				return;
			m_vertex[i*image->m_width*3+j*3+0] = j * m_zoom[0];
			m_vertex[i*image->m_width*3+j*3+1] = i * m_zoom[1];
			m_vertex[i*image->m_width*3+j*3+2] = height / 255.0 * m_zoom[2];
			
			if (max[0] < j * m_zoom[0])
				max[0] = j * m_zoom[0]; 
			if (max[1] < i * m_zoom[1])
				max[1] = i * m_zoom[1]; 
			if (max[2] < height / 255.0 * m_zoom[2])
				max[2] = height / 255.0 * m_zoom[2]; 
			
			if (min[0] > j * m_zoom[0])
				min[0] = j * m_zoom[0]; 
			if (min[1] > i * m_zoom[1])
				min[1] = i * m_zoom[1]; 
			if (min[2] > height / 255.0 * m_zoom[2])
				min[2] = height / 255.0 * m_zoom[2]; 

			m_texture[i*image->m_width*2+j*2+0] = (float)j/(float)image->m_width;
			m_texture[i*image->m_width*2+j*2+1] = (float)i/(float)image->m_height;
		}
	}

	//
	//	center vertex at zero
	//
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertex[3*i + 0] -= (max[0]+min[0])/2;
		m_vertex[3*i + 1] -= (max[1]+min[1])/2;
		if (	m_vertex[3*i + 1] > 100)
			i = i;
		m_vertex[3*i + 2] -= (max[2]+min[2])/2;
	}

	for (int i = 0; i < image->m_height-1; i++)
	{
		for (int j = 0; j < image->m_width-1; j++)
		{
			m_index[i*(image->m_width-1)*6+j*6+0] = (i+1)*image->m_width+j;
			m_index[i*(image->m_width-1)*6+j*6+1] = i*image->m_width+j;
			m_index[i*(image->m_width-1)*6+j*6+2] = i*image->m_width+j+1;

			m_index[i*(image->m_width-1)*6+j*6+3] = (i+1)*image->m_width+j;
			m_index[i*(image->m_width-1)*6+j*6+4] = i*image->m_width+j+1;
			m_index[i*(image->m_width-1)*6+j*6+5] = (i+1)*image->m_width+j+1;

			float n[3];
			//
			//	normal for first triangle
			//
			float* v0 = m_vertex + 3*((i+1)*image->m_width+j);
			float* v1 = m_vertex + 3*(i*image->m_width+j);
			float* v2 = m_vertex + 3*(i*image->m_width+j+1);

			float a[3];
			a[0] = v2[0] - v0[0]; a[1] = v2[1] - v0[1]; a[2] = v2[2] - v0[1];
			float b[3];
			b[0] = v1[0] - v0[0]; b[1] = v1[1] - v0[1]; b[2] = v1[2] - v0[1];

			n[0] = a[1] * b[2] - a[2] * b[1];
			n[1] = a[2] * b[0] - a[0] * b[2];
			n[2] = a[0] * b[1] - a[1] * b[0];

			m_normals[3*((i+1)*image->m_width+j) + 0] += n[0];
			m_normals[3*((i+1)*image->m_width+j) + 1] += n[1];
			m_normals[3*((i+1)*image->m_width+j) + 2] += n[2];

			m_normals[3*(i*image->m_width+j) + 0] += n[0];
			m_normals[3*(i*image->m_width+j) + 1] += n[1];
			m_normals[3*(i*image->m_width+j) + 2] += n[2];
			
			m_normals[3*(i*image->m_width+j+1) + 0] += n[0];
			m_normals[3*(i*image->m_width+j+1) + 1] += n[1];
			m_normals[3*(i*image->m_width+j+1) + 2] += n[2];

			//
			//	normal for second triangle
			//
			v0 = m_vertex + 3*((i+1)*image->m_width+j);
			v1 = m_vertex + 3*(i*image->m_width+j+1);
			v2 = m_vertex + 3*((i+1)*image->m_width+j+1);

			a[0] = v2[0] - v0[0]; a[1] = v2[1] - v0[1]; a[2] = v2[2] - v0[1];
			b[0] = v1[0] - v0[0]; a[1] = v1[1] - v0[1]; a[2] = v1[2] - v0[1];

			n[0] = a[1] * b[2] - a[2] * b[1];
			n[1] = a[2] * b[0] - a[0] * b[2];
			n[2] = a[0] * b[1] - a[1] * b[0];

			m_normals[3*((i+1)*image->m_width+j) + 0] += n[0];
			m_normals[3*((i+1)*image->m_width+j) + 1] += n[1];
			m_normals[3*((i+1)*image->m_width+j) + 2] += n[2];

			m_normals[3*(i*image->m_width+j+1) + 0] += n[0];
			m_normals[3*(i*image->m_width+j+1) + 1] += n[1];
			m_normals[3*(i*image->m_width+j+1) + 2] += n[2];
			
			m_normals[3*((i+1)*image->m_width+j+1) + 0] += n[0];
			m_normals[3*((i+1)*image->m_width+j+1) + 1] += n[1];
			m_normals[3*((i+1)*image->m_width+j+1) + 2] += n[2];
		}
	}

	//
	//	normalize all normals
	//
	for (int i = 0; i < m_vertexCount; i++)
	{
		float l = sqrt(m_normals[3*i+0]*m_normals[3*i+0]+
			m_normals[3*i+1]*m_normals[3*i+1]+
			m_normals[3*i+2]*m_normals[3*i+2]);

		m_normals[3*i+0] /= l;
		m_normals[3*i+1] /= l;
		m_normals[3*i+2] /= l;
	}
}

void Terrain::SetTransform(float* transform)
{
	memcpy(m_transform, transform, sizeof(m_transform));
}

void Terrain::SetPosition(float x, float y, float z)
{
	m_transform[12] = x;
	m_transform[13] = y;
	m_transform[14] = z;
}

void Terrain::SetTexture(unsigned int id, unsigned name)
{
	m_textures[id] = name;
}

void Terrain::SetEnvironmentMap(unsigned int id, unsigned int texture)
{
	m_envMapID = id;
	m_textures[id] = texture;
}#include "Terrain.h"
#include <math.h>
#include "../Util/Image.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glext.h>
#include "Texture2D.h"
#include "Driver.h"

Terrain::Terrain() : m_maxTextures(g_driver->GetMaxTextureUnits())
{
	m_zoom[0] = 0.1f;
	m_zoom[1] = 0.1f;
	m_zoom[2] = 2;
	memset(m_transform, 0, sizeof(m_transform));
	m_transform[0] = m_transform[5] = m_transform[10] = m_transform[15] = 1.0f;
	m_textures = new unsigned[m_maxTextures];
	memset(m_textures, 0, sizeof(TTexture2D)*m_maxTextures);
	m_envMapID = -1;
}

Terrain::~Terrain()
{
}

void Terrain::Draw()
{
	InternalDraw_v3();
}

//
//	use texture combiner for microrelief
//	0 - main texture
//	1 - detail texture
//
void Terrain::InternalDraw_v3()
{
	glPushMatrix();
	//glLoadIdentity();
	glMultMatrixf(m_transform);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_vertex);
	glEnableClientState(GL_NORMAL_ARRAY);	
	glNormalPointer(GL_FLOAT, 0, m_normals);
	
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);			
	glTexCoordPointer(2, GL_FLOAT, 0, m_texture);
	glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_REPLACE);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glTexCoordPointer(2, GL_FLOAT, 0, m_texture);
	glBindTexture(GL_TEXTURE_2D, m_textures[1]);
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glScalef(30, 30, 30);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);
	//	arg0
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR);
	//	arg1
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR);
	
	glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);/**/

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, m_index);/**/
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	for (int i = 0; i < m_maxTextures; i++)
	{
		glClientActiveTextureARB(GL_TEXTURE0_ARB+i);
		glActiveTextureARB(GL_TEXTURE0_ARB+i);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}/**/	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();/**/
}

//
//	use texture and pointers
//
void Terrain::InternalDraw_v1()
{
	glPushMatrix();
	//glLoadIdentity();
	glMultMatrixf(m_transform);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_vertex);
	glNormalPointer(GL_FLOAT, 0, m_normals);

	for (int i = 0; i < m_maxTextures; i++)
	{	
		if (m_textures[i])
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
				glBindTexture(GL_TEXTURE_2D, m_textures[i]);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
			}
			else
			{
				glMatrixMode(GL_TEXTURE);
				glLoadIdentity();
				glScalef(30,30,30);
				glTexCoordPointer(2, GL_FLOAT, 0, m_texture);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
				glBindTexture(GL_TEXTURE_2D, m_textures[i]);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);				
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
			}
		}

	}/**/
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, m_index);/**/

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

void Terrain::InternalDraw_v2()
{
	for (int i = 0; i < m_indexCount / 3; i += 3)
	{
		glBegin(GL_TRIANGLES);
		glVertex3fv(&m_vertex[m_index[i+0]]);
		glVertex3fv(&m_vertex[m_index[i+1]]);
		glVertex3fv(&m_vertex[m_index[i+2]]);
		glEnd();
	}
}

void Terrain::SetZoom(float zoom[])
{
	memcpy(m_zoom, zoom, sizeof(m_zoom));;
}

void Terrain::Update(float delta)
{
}

void Terrain::GenerateFromHeightMap(const Image* image)
{
	float height = 0;
	int step = sizeof(char)*image->m_bitsPerPixel/8;
	m_vertexCount = (image->m_width+1)*(image->m_height+1);
	m_indexCount = (image->m_width-1)*(image->m_height-1)*2*3;
	m_vertex = new float[m_vertexCount*sizeof(float)*3];
	m_normals = new float[m_vertexCount*sizeof(float)*3];
	memset(m_normals, 0, sizeof(float)*3*m_vertexCount);
	m_texture = new float[m_vertexCount*sizeof(float)*2];
	m_index = new unsigned[m_indexCount];
	float max[3] = {-1e+32, -1e+32, -1e+32};
	float min[3] = {1e+32, 1e+32, 1e+32};
	for (int i = 0; i < image->m_height; i++)
	{
		for (int j = 0; j < image->m_width; j++)
		{
			float height;
			if (image->m_bitsPerPixel>>3 == 1)
			{
				height = image->m_data[i*image->m_width+j];
			}
			else if (image->m_bitsPerPixel>>3 == 3)
			{
				height = (image->m_data[i*image->m_width*step+j*step + 0]+
					image->m_data[i*image->m_width*step+j*step + 1]+
					image->m_data[i*image->m_width*step+j*step + 2])/3;
			}
			else
				return;
			m_vertex[i*image->m_width*3+j*3+0] = j * m_zoom[0];
			m_vertex[i*image->m_width*3+j*3+1] = i * m_zoom[1];
			m_vertex[i*image->m_width*3+j*3+2] = height / 255.0 * m_zoom[2];
			
			if (max[0] < j * m_zoom[0])
				max[0] = j * m_zoom[0]; 
			if (max[1] < i * m_zoom[1])
				max[1] = i * m_zoom[1]; 
			if (max[2] < height / 255.0 * m_zoom[2])
				max[2] = height / 255.0 * m_zoom[2]; 
			
			if (min[0] > j * m_zoom[0])
				min[0] = j * m_zoom[0]; 
			if (min[1] > i * m_zoom[1])
				min[1] = i * m_zoom[1]; 
			if (min[2] > height / 255.0 * m_zoom[2])
				min[2] = height / 255.0 * m_zoom[2]; 

			m_texture[i*image->m_width*2+j*2+0] = (float)j/(float)image->m_width;
			m_texture[i*image->m_width*2+j*2+1] = (float)i/(float)image->m_height;
		}
	}

	//
	//	center vertex at zero
	//
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertex[3*i + 0] -= (max[0]+min[0])/2;
		m_vertex[3*i + 1] -= (max[1]+min[1])/2;
		if (	m_vertex[3*i + 1] > 100)
			i = i;
		m_vertex[3*i + 2] -= (max[2]+min[2])/2;
	}

	for (int i = 0; i < image->m_height-1; i++)
	{
		for (int j = 0; j < image->m_width-1; j++)
		{
			m_index[i*(image->m_width-1)*6+j*6+0] = (i+1)*image->m_width+j;
			m_index[i*(image->m_width-1)*6+j*6+1] = i*image->m_width+j;
			m_index[i*(image->m_width-1)*6+j*6+2] = i*image->m_width+j+1;

			m_index[i*(image->m_width-1)*6+j*6+3] = (i+1)*image->m_width+j;
			m_index[i*(image->m_width-1)*6+j*6+4] = i*image->m_width+j+1;
			m_index[i*(image->m_width-1)*6+j*6+5] = (i+1)*image->m_width+j+1;

			float n[3];
			//
			//	normal for first triangle
			//
			float* v0 = m_vertex + 3*((i+1)*image->m_width+j);
			float* v1 = m_vertex + 3*(i*image->m_width+j);
			float* v2 = m_vertex + 3*(i*image->m_width+j+1);

			float a[3];
			a[0] = v2[0] - v0[0]; a[1] = v2[1] - v0[1]; a[2] = v2[2] - v0[1];
			float b[3];
			b[0] = v1[0] - v0[0]; b[1] = v1[1] - v0[1]; b[2] = v1[2] - v0[1];

			n[0] = a[1] * b[2] - a[2] * b[1];
			n[1] = a[2] * b[0] - a[0] * b[2];
			n[2] = a[0] * b[1] - a[1] * b[0];

			m_normals[3*((i+1)*image->m_width+j) + 0] += n[0];
			m_normals[3*((i+1)*image->m_width+j) + 1] += n[1];
			m_normals[3*((i+1)*image->m_width+j) + 2] += n[2];

			m_normals[3*(i*image->m_width+j) + 0] += n[0];
			m_normals[3*(i*image->m_width+j) + 1] += n[1];
			m_normals[3*(i*image->m_width+j) + 2] += n[2];
			
			m_normals[3*(i*image->m_width+j+1) + 0] += n[0];
			m_normals[3*(i*image->m_width+j+1) + 1] += n[1];
			m_normals[3*(i*image->m_width+j+1) + 2] += n[2];

			//
			//	normal for second triangle
			//
			v0 = m_vertex + 3*((i+1)*image->m_width+j);
			v1 = m_vertex + 3*(i*image->m_width+j+1);
			v2 = m_vertex + 3*((i+1)*image->m_width+j+1);

			a[0] = v2[0] - v0[0]; a[1] = v2[1] - v0[1]; a[2] = v2[2] - v0[1];
			b[0] = v1[0] - v0[0]; a[1] = v1[1] - v0[1]; a[2] = v1[2] - v0[1];

			n[0] = a[1] * b[2] - a[2] * b[1];
			n[1] = a[2] * b[0] - a[0] * b[2];
			n[2] = a[0] * b[1] - a[1] * b[0];

			m_normals[3*((i+1)*image->m_width+j) + 0] += n[0];
			m_normals[3*((i+1)*image->m_width+j) + 1] += n[1];
			m_normals[3*((i+1)*image->m_width+j) + 2] += n[2];

			m_normals[3*(i*image->m_width+j+1) + 0] += n[0];
			m_normals[3*(i*image->m_width+j+1) + 1] += n[1];
			m_normals[3*(i*image->m_width+j+1) + 2] += n[2];
			
			m_normals[3*((i+1)*image->m_width+j+1) + 0] += n[0];
			m_normals[3*((i+1)*image->m_width+j+1) + 1] += n[1];
			m_normals[3*((i+1)*image->m_width+j+1) + 2] += n[2];
		}
	}

	//
	//	normalize all normals
	//
	for (int i = 0; i < m_vertexCount; i++)
	{
		float l = sqrt(m_normals[3*i+0]*m_normals[3*i+0]+
			m_normals[3*i+1]*m_normals[3*i+1]+
			m_normals[3*i+2]*m_normals[3*i+2]);

		m_normals[3*i+0] /= l;
		m_normals[3*i+1] /= l;
		m_normals[3*i+2] /= l;
	}
}

void Terrain::SetTransform(float* transform)
{
	memcpy(m_transform, transform, sizeof(m_transform));
}

void Terrain::SetPosition(float x, float y, float z)
{
	m_transform[12] = x;
	m_transform[13] = y;
	m_transform[14] = z;
}

void Terrain::SetTexture(unsigned int id, unsigned name)
{
	m_textures[id] = name;
}

void Terrain::SetEnvironmentMap(unsigned int id, unsigned int texture)
{
	m_envMapID = id;
	m_textures[id] = texture;
}