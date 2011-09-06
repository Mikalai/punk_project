
#include <stdio.h>
#include <memory.h>
//#include <gl3/gl3.h>
#include "surface.h"

namespace ImageLoader
{
	//******************************************************
	//	Surface part
	//******************************************************
	Surface::Surface() : width(0), height(0), depth(0), size(0), data(0)
	{
#ifdef _DEBUG
		//printf("%d: Surface()\n", constructorCount++);
#endif
	}

	Surface::Surface(int w, int h, int d, unsigned s) :
	width(w),
		height(h),
		depth(d),
		size(s)
	{
#ifdef _DEBUG
		//printf("%d: Surface()\n", constructorCount++);
#endif
		data = new unsigned char[size];
	}

	Surface::~Surface()
	{
#ifdef _DEBUG
		//printf("%d: Surface()\n", destructorCount++);
#endif
		if (data)
		{
			delete[] data;
			data = NULL;
		}
	}

	Surface::Surface(const Surface& s)
	{
		//Clear();
		width = s.width;
		height = s.height;
		depth = s.depth;
		size = s.size;

		data = new unsigned char[size];
		memcpy(data, s.data, size);
	}

	Surface& Surface::operator =(const Surface& s)
	{
		if (this != &s)
		{
			Clear();
			width = s.width;
			height = s.height;
			depth = s.depth;
			size = s.size;

			data = new unsigned char[size];
			memcpy(data, s.data, size);
		}
		return *this;
	}

	void Surface::Clear()
	{
		if (data)
		{
			delete [] data;
			data = 0;
		}
	}
	void Surface::Create(int w, int h, int d, int imgsize)
	{
		Clear();
		width = w;
		height = h;
		depth = d;
		size = imgsize;
		data = new unsigned char[imgsize];
	}

	void Surface::PutLine(int y, int numComponents, unsigned long* bits)
	{
		if ( y < 0 || y >= height )
			return;

		int offs = y * width * numComponents;
		unsigned char * ptr  = data + offs;

		if ( numComponents == 4 )				// RGBA ImageFile
			memcpy ( ptr, bits, 4 * width );
		else
			if ( numComponents == 3 )				// RGB ImageFile
			{
				unsigned char * src = (unsigned char *) bits;

				for ( int i = 0; i < width; i++, src += 4 )
				{
					*ptr++ = src [0];
					*ptr++ = src [1];
					*ptr++ = src [2];
				}
			}
			else
				if ( numComponents == 1 )				// greyscale ImageFile
				{
					for ( int i = 0; i < width ; i++, bits++ )
						*ptr++ = *(unsigned char *) bits;
				}
	}
}
