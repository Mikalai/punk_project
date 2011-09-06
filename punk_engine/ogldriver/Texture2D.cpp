#include "Texture2D.h"
#include "Driver.h"
#include <stdio.h>

TTexture2D::TTexture2D() : m_textureName(0)
{}

TTexture2D::~TTexture2D()
{
	if (m_textureName)
		glDeleteTextures(1, &m_textureName);
#ifdef _DEBUG
	printf("~TTexture2D()\n");
#endif
}

bool TTexture2D::Create(Image *image)
{
	glGenTextures(1, &m_textureName);
	glBindTexture(GL_TEXTURE_2D, m_textureName);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->m_width, image->m_height, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, image->m_data);


/*	if (gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image->GetWidth(), image->GetHeight(), GL_RGB, 
		GL_UNSIGNED_BYTE, image->GetData()) != 0)
		throw Exception("Can't build mip maps");*/
	return true;
}

void TTexture2D::Apply()
{
	GLboolean isTextureEnabled;
	glGetBooleanv(GL_TEXTURE_2D, &isTextureEnabled);
	if (isTextureEnabled)
	{
		//glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_textureName);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
}

unsigned TTexture2D::Id() const
{
	return m_textureName;
}#include "Texture2D.h"
#include "Driver.h"
#include <stdio.h>

TTexture2D::TTexture2D() : m_textureName(0)
{}

TTexture2D::~TTexture2D()
{
	if (m_textureName)
		glDeleteTextures(1, &m_textureName);
#ifdef _DEBUG
	printf("~TTexture2D()\n");
#endif
}

bool TTexture2D::Create(Image *image)
{
	glGenTextures(1, &m_textureName);
	glBindTexture(GL_TEXTURE_2D, m_textureName);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->m_width, image->m_height, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, image->m_data);


/*	if (gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image->GetWidth(), image->GetHeight(), GL_RGB, 
		GL_UNSIGNED_BYTE, image->GetData()) != 0)
		throw Exception("Can't build mip maps");*/
	return true;
}

void TTexture2D::Apply()
{
	GLboolean isTextureEnabled;
	glGetBooleanv(GL_TEXTURE_2D, &isTextureEnabled);
	if (isTextureEnabled)
	{
		//glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_textureName);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
}

unsigned TTexture2D::Id() const
{
	return m_textureName;
}