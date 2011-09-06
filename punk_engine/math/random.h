#ifndef _H_PUNK_RANDOM
#define _H_PUNK_RANDOM

#include "config.h"

namespace Math
{
	class LIB_MATH Random
	{
		unsigned m_x;
	public:
		Random();
		float Uniform(float a = 0.0f, float b = 1.0f);	
		float Uniform(int x, float a = -1.0f, float b = 1.0f);
		float UniformNormalized(int x);
	};
}

#endif