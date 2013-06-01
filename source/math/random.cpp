#include "math_error.h"
#include "random.h"
#include <time.h>
#include <stdlib.h>

namespace Math
{
	Random::Random()
	{
		m_mod = 2147483647;
		m_a = 524287;
		m_b = 131071;
        m_x = 1;
	};

	Random::Random(uint64_t seed)
	{
		m_mod = 2147483647;
		m_a = 524287;
		m_b = 131071;

		m_x = seed;
	}

	uint64_t Random::Uniformi()
	{
		m_x = (m_a * m_x + m_b) % m_mod;
		return m_x;
	}

	double Random::Uniform()
	{
		m_x = Uniformi();
		return (m_x + 1) / (double)m_mod;
	}

	double Random::Uniform(double a, double b)
	{
		double v = Uniform();
		return a + v * (b - a);
	}

	void Random::SetSeed(uint64_t value)
	{
		m_x = value;
	}

	float Random::Noise(int x)
	{
		x = ( x << 13 ) ^ x;
		return float( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
	}
}
