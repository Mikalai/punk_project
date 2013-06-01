#ifndef _H_PUNK_RANDOM
#define _H_PUNK_RANDOM

#include <cstdint>
#include "../config.h"

namespace Math
{
	class PUNK_ENGINE_PUBLIC Random
	{
		uint64_t m_x;
		uint64_t m_mod;
		uint64_t m_a;
		uint64_t m_b;
	public:
		Random();
		Random(uint64_t seed);

		void SetSeed(uint64_t value);

		uint64_t Uniformi();

		/**
		*	Returns a random number in the range [0; 1]
		*/
		double Uniform();

		/**
		*	Returns a random number in the range [a; b]
		*/
		double Uniform(double a, double b);

		float Noise(int x);

	};
}

#endif
