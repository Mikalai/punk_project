#include "math_error.h"
#include "random.h"
#include <time.h>
#include <stdlib.h>

namespace Math
{
	Random::Random()
	{
		time_t t;
		time(&t);
		m_x = t;
	};

	Random::Random(unsigned seed) : m_x(seed)
	{
	}

	float Random::UniformNormalized(int x)
	{		
		m_x = x;
		m_x = (m_x << 13) ^ m_x;
		return ( 1.0f - ( (m_x * (m_x * m_x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
	}

	float Random::Uniform(float a, float b)
	{
		float t = (float)rand()/(float)RAND_MAX;
		return a + (b-a)*t;
	}/**/
	/*	unsigned long temp;
		float fran;
		static unsigned long jflone=0x3f800000;
		static unsigned long jflmsk=0x007fffff;

		m_x = 1664525L*m_x+1013904223L;
		temp = jflone | (jflmsk & m_x);
		fran = (*(float*)&temp)-1.F;

		return a + (b - a) * (float)fran;
	}/**/

	float Random::Uniform(int x, float a, float b)
	{
		//srand(x);
		m_x = x;
		return Uniform(a, b);
	}
}