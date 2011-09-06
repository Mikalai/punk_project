/*
	File: TextureWithMipMap.h
	Author: Abramov Nickolai
	Description: Contains a TextureWithMipMap class, a texture with mip maps
*/

#ifndef _H_TextureWithMipMap
#define _H_TextureWithMipMap

class TextureWithMipMap
{
public:
	~TextureWithMipMap();
	void Create(GLint width, GLint height, GLenum format, GLint components, GLubyte* data);
	operator GLuint();
private:
	GLint m_width;
	GLint m_height;
	GLenum m_format;
	GLuint m_id;
};

#endif	_H_TextureWithMipMap