#ifndef _H_PUNK_SOFT_VIDEO_BUFFER_WIN32
#define _H_PUNK_SOFT_VIDEO_BUFFER_WIN32

#include "../punk_engine/math/math.h"

namespace Video
{
	inline PixelRGBA RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		PixelRGBA p;
		p.pixel = a << 24 | b << 16 | g << 8 | r;
		return p;
	}

	struct PixelRGBA
	{
		union
		{
			struct
			{
				unsigned char r, g, b, a;
			};
			unsigned pixel;
		};
	};

	typedef Math::MatrixNxM<float> DepthBuffer;
	typedef Math::MatrixNxM<PixelRGBA> ColorBuffer;
	typedef Math::MatrixNxM<unsigned> StencilBuffer;
}

#endif