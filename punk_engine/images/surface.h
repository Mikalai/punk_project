/*
	File: Surface.h
	Author: Nickolai Abramov
	Desc: Surface with image data
*/

#ifndef _H_PUNK_SURFACE
#define _H_PUNK_SURFACE

namespace ImageLoader
{
	struct Surface
	{
		Surface();
		Surface(const Surface&);
		Surface(int w, int h, int d, unsigned s);
		~Surface();
		int width;
		int height;
		int depth;
		unsigned size;	
		unsigned char* data;

		void Create(int w, int h, int d, int imgsize);
		void Clear();
		void PutLine(int y, int numComponents, unsigned long* data);

		Surface& operator = (const Surface& s);
	};
}

#endif	//	_H_PUNK_SURFACE