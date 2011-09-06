/*
	File: TextureWithAnisotropy.cpp
	Author: Abramov Nickolai
	Description: TextureWithAnisotropy implementation
*/
#include "Os.h"
#include "TextureWithAnisotropy.h"

void TextureWithAnisotropy::Create(GLint width, GLint height, GLenum format, GLint components, GLubyte* data)
{
	glGenTextures(1, &m_id);
	CheckError("TextureWithAnisotropy::Create() -> glGenTextures() failed");
	glBindTexture(GL_TEXTURE_2D, m_id);
	CheckError("TextureWithAnisotropy::Create() -> glBindTexture() failed");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	CheckError("TextureWithAnisotropy::Create() -> glTexParameterf() failed");
	glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	CheckError("TextureWithAnisotropy::Create() -> glTexImage2D() failed");
}

TextureWithAnisotropy::~TextureWithAnisotropy()
{
	glDeleteTextures(1, &m_id);
	CheckError("TextureWithAnisotropy::~TextureWithAnisotropy() -> glDeleteTextures() failed");
}

TextureWithAnisotropy::operator GLuint()
{
	return m_id;
}

void TextureWithAnisotropy::SetAnisotropy(int value)
{
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &m_maxAnisotropy);
	CheckError("TextureWithAnisotropy::SetAnisotropy() -> glGetIntegerv() failed");
	if (value < m_maxAnisotropy)
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
		CheckError("TextureWithAnisotropy::SetAnisotropy() -> glBindTexture() failed");
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, value);
		CheckError("TextureWithAnisotropy::SetAnisotropy() -> glTexParameteri() failed");
	}
}