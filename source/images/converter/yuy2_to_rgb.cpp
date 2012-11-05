#include "yuy2_to_rgb.h"
#include "../../system/logger.h"
#include "../../math/helper.h"

namespace ImageModule
{
	bool YUY2toRGB(const unsigned char* src, int length, unsigned char* dst, int* out_length)
	{
		using namespace Math;

		if (dst)
		{
			if (!out_length)
				return (out_error() << "Bad size pointer of destination buffer" << std::endl, false);

			if (*out_length < ((length * 6) >> 2))
				return (out_error() << "Bad destination buffer size: " << *out_length << ". Shoudl be: " << ((length * 6) >> 2) << std::endl, false);

			int i;

#pragma omp for
			for ( int i = 0; i < length; i += 4 )
			{
				int y0 = src[i];
				int u0 = src[i+1];
				int y1 = src[i+2];
				int v0 = src[i+3];		

				float f[16] = {1.164383f,  1.596027f,  0.000f, -222.912f,
					1.164383f, -0.813000f, -0.391f,  135.488f,
					1.164383f,  0.000000f,  2.018f, -276.928f};
				float v1[4] = {y0, v0, u0, 1};
				float v2[4] = {y1, v0, u0, 1};

				float a1[4];
				float a2[4];
				__asm 
				{					
					movups xmm0, v1;
					movups xmm1, f;
					movups xmm2, f+0x10;
					movups xmm3, f+0x20;
					dpps xmm1, xmm0, 241;
					dpps xmm2, xmm0, 241;
					dpps xmm3, xmm0, 241;					
					shufps xmm1, xmm2, 00000000b;					
					shufps xmm1, xmm3, 00001100b;
					movups a1, xmm1;					

					movups xmm0, v2;
					movups xmm1, f;
					movups xmm2, f+0x10;
					movups xmm3, f+0x20;
					dpps xmm1, xmm0, 241;
					dpps xmm2, xmm0, 241;
					dpps xmm3, xmm0, 241;					
					shufps xmm1, xmm2, 00000000b;					
					shufps xmm1, xmm3, 00001100b;
					movups a2, xmm1;					
				}

				dst[0] = Clamp( 0, 255, (int)a1[0]);
				dst[1] = Clamp( 0, 255, (int)a1[1]);
				dst[2] = Clamp( 0, 255, (int)a1[2]);
				dst[3] = Clamp( 0, 255, (int)a2[0]);
				dst[4] = Clamp( 0, 255, (int)a2[1]);
				dst[5] = Clamp( 0, 255, (int)a2[2]);
				dst += 6;
			}
		}
		else
		{
			if (!out_length)
				return (out_error() << "Invalid arguments for conversion from YUY2 to RGB" << std::endl, false);
			*out_length = (length * 6) >> 2;
		}
	}
}