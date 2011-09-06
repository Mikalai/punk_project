/*
	File: CubeMap.h
	Author: Abramov Nickolai
	Description: Contains a cube map
*/

#ifndef _H_CUBE_MAP
#define _H_CUBE_MAP

#include "../images/image_loader.h"

class CubeMap
{
public:
	~CubeMap();
	void Create(ImageLoader::ImageFile* surface[]);
	void Create(ImageLoader::ImageFile* surface);
	operator GLuint();
	static CubeMap CreateNormalizationCubeMap(int size);
	void Dispose();
private:
	GLint m_width;
	GLint m_height;
	GLenum m_format;
	GLuint m_id;
};

#endif	// _H_CUBE_MAP
