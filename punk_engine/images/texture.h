/*
File: Texture.h
Author: Nickoalai Abramov
Desc: OpenGL Texture
*/

#ifndef _H_PUNK_TEXTURE
#define _H_PUNK_TEXTURE

#include <vector>
#include "surface.h"

namespace ImageLoader
{
	struct Texture
	{
		Texture(const Texture &copy);
		Texture &operator= (const Texture &rhs);
		Texture();
		Texture(int w, int h, int d, unsigned s);
		int width;
		int height;
		int depth;
		unsigned size;
		Surface surface;
		std::vector<Surface> mipmaps;
	};
}

#endif	// _H_PUNK_TEXTURE
