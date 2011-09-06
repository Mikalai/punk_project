/*
	File: CubeMap.cpp
	Author: Abramov Nickolai
	Description: CubeMap implementation
*/
#include "os.h"
#include "cube_map.h"

void CubeMap::Create(ImageLoader::ImageFile* surface[])
{
	//glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &m_id);
	CheckError("CubeMap::Create() -> glGenTextures() failed");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	CheckError("CubeMap::Create() -> glPixelStore() failed");
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
	CheckError("CubeMap::Create() -> glBindTexture() failed");
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	CheckError("CubeMap::Create() -> glTexParameterf() failed");
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);
	CheckError("CubeMap::Create() -> glTexParameteri() failed");

	for (int i= 0; i < 6; i++)
	{
		//glTexParameteri(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, surface[i]->components,
			surface[i]->textures[0].width,
			surface[i]->textures[0].height, 0,
			surface[i]->format, GL_UNSIGNED_BYTE,
			surface[i]->textures[0].surface.data);
		CheckError("CubeMap::Create() -> glTexImage2D() failed");
	}
}

void CubeMap::Create(ImageLoader::ImageFile* surface)
{
	if (!surface->cubemap)
		throw System::Exception("Current surface is not cubemap");

	glGenTextures(1, &m_id);
	CheckError("CubeMap::Create() -> glGenTextures() failed");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	CheckError("CubeMap::Create() -> glPixelStorei() failed");
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
	CheckError("CubeMap::Create() -> glBindTexture() failed");
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	CheckError("CubeMap::Create() -> glTexParameterf() failed");
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	CheckError("CubeMap::Create() -> glTexParameteri() failed");

	for (int i= 0; i < 6; i++)
	{
		//glTexParameteri(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, surface->components,
			surface->textures[i].width,
			surface->textures[i].height, 0,
			surface->format, GL_UNSIGNED_BYTE,
			surface->textures[i].surface.data);
		CheckError("CubeMap::Create() -> glTexImage2D() failed");
	}
}

CubeMap::~CubeMap()
{
}

void CubeMap::Dispose()
{
	glDeleteTextures(1, &m_id);
	CheckError("CubeMap::~CubeMap() -> glDeleteTextures() failed");
}

CubeMap::operator GLuint()
{
	return m_id;
}

void GetCubeVector(int side, int cubeSize, int x, int y, float* v)
{
	float s = ((float)x+0.5f)/(float)cubeSize;
	float t = ((float)y+0.5f)/(float)cubeSize;
	float sc = 2*s - 1;
	float tc = 2*t - 1;
	switch(side)
	{
	case 0:
		v[0] = 1; v[1] = -tc; v[2] = -sc;
		break;
	case 1:
		v[0] = -1; v[1] = -tc; v[2] = sc;
		break;
	case 2:
		v[0] = sc; v[1] = 1; v[2] = tc;
		break;
	case 3:
		v[0] = sc; v[1] = -1; v[2] = -tc;
		break;
	case 4:
		v[0] = sc; v[1] = -tc; v[2] = 1;
		break;
	case 5:
		v[0] = -sc; v[1] = -tc; v[2] = -1;
		break;
	}
	float c = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0] /= c;
	v[1] /= c;
	v[2] /= c;
}

CubeMap CubeMap::CreateNormalizationCubeMap(int cubeSize)
{
	CubeMap map;
	map.m_format = GL_RGB;
	map.m_width = map.m_height = cubeSize;

	float v[3];
	GLubyte* pixel = new GLubyte[3*cubeSize*cubeSize];
	if (pixel == NULL)
		throw System::Exception("Can't create normalization cube map");
	glGenTextures(1, &map.m_id);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, map.m_id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int side = 0; side < 6; side++)
	{
		for (int x = 0; x < cubeSize; x++)
		{
			for (int y = 0; y < cubeSize; y++)
			{
				int offs = 3*(y*cubeSize+x);
				GetCubeVector(side, cubeSize, x, y, v);
				pixel[offs + 0] = GLubyte(128 + 127*v[0]);
				pixel[offs + 1] = GLubyte(128 + 127*v[1]);
				pixel[offs + 2] = GLubyte(128 + 127*v[2]);
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+side, 0, GL_RGB,
			cubeSize, cubeSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel);
	}
	delete[] pixel;

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_CUBE_MAP);

	return map;
}
