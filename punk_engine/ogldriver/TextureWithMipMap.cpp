/*
	File: TextureWithMipMap.cpp
	Author: Abramov Nickolai
	Description: TextureWithMipMap implementation
*/
#include "Os.h"
#include "TextureWithMipMap.h"

void TextureWithMipMap::Create(GLint width, GLint height, GLenum format, GLint components, GLubyte* data)
{
	glGenTextures(1, &m_id);
	CheckError("TextureWithMipMap::Create() -> glGenTextures() failed");
	glBindTexture(GL_TEXTURE_2D, m_id);
	CheckError("TextureWithMipMap::Create() -> glBindTexture() failed");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	CheckError("TextureWithMipMap::Create() -> glTexParameterf() failed");
	glHint(GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);
	CheckError("TextureWithMipMap::Create() -> glHint() failed");
	glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	CheckError("TextureWithMipMap::Create() -> glTexImage2D() failed");
}

TextureWithMipMap::~TextureWithMipMap()
{
	glDeleteTextures(1, &m_id);
	CheckError("TextureWithMipMap::~TextureWithMipMap() -> glDeleteTextures() failed");
}

TextureWithMipMap::operator GLuint()
{
	return m_id;
}