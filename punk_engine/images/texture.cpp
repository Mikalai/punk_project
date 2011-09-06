
#include "texture.h"

namespace ImageLoader
{
	//************************************************************
	//	Texture implementation
	//************************************************************
	Texture::Texture() : width(0), height(0), depth(0), size(0)
	{	}

	Texture::Texture(int w, int h, int d, unsigned s) :
	width(w),
		height(h),
		depth(d),
		size(s),
		surface(w,h,d,s)
	{}

	Texture::Texture(const Texture &copy)
	{
		surface.Clear();
		width = copy.width;
		height = copy.height;
		depth = copy.depth;
		size = copy.size;
		mipmaps.clear();

		surface = copy.surface;

		for (unsigned int i = 0; i < copy.mipmaps.size(); i++)
			mipmaps.push_back(copy.mipmaps[i]);
	}

	Texture &Texture::operator= (const Texture &rhs)
	{
		surface.Clear();

		if (this != &rhs)
		{
			size = rhs.size;
			width = rhs.width;
			height = rhs.height;
			depth = rhs.depth;

			surface = rhs.surface;
		}

		return *this;
	}

}
