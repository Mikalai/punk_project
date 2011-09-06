/*
	File: TextureWithAnisotropy.h
	Author: Abramov Nickolai
	Description: Contains a TextureWithAnisotropy class
*/

#ifndef _H_TEXTURE_WITH_ANIS
#define _H_TEXTURE_WITH_ANIS

class TextureWithAnisotropy
{
public:
	~TextureWithAnisotropy();
	void Create(GLint width, GLint height, GLenum format, GLint components, GLubyte* data);
	void SetAnisotropy(int value);
	operator GLuint();
private:
	GLint m_width;
	GLint m_height;
	GLenum m_format;
	GLuint m_id;
	GLint m_maxAnisotropy;
};

#endif	//	_H_TEXTURE_WITH_ANIS