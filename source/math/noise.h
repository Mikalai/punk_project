#ifndef _H_PUNK_PERLIN_NOISE
#define _H_PUNK_PERLIN_NOISE

#include "../config.h"

namespace Math
{
	class PUNK_ENGINE Noise
	{
		int m_max_octaves;
		float m_persistence;

	public:
		Noise();

		void SetOctavesCount(int value);
		void SetPersistance(float value);
		int GetOctavesCount() const;
		float GetPersistance() const;

		float Noise1D(int x);
		float SmoothedNoise1D(int x);
		float InterpolatedNoise1D(float x);
		float PerlinNoise1D(float x);

		float Noise2D(int x, int y);
		float SmoothedNoise2D(int x, int y);
		float InterpolatedNoise2D(float x, float y);
		float PerlinNoise2D(float x, float y);

		float Noise3D(int x, int y, int z);
		float SmoothedNoise3D(int x, int y, int z);
		float InterpolatedNoise3D(float x, float y, float z);
		float PerlinNoise3D(float x, float y, float z);

		float Noise4D(int x, int y, int z, int w);
		float SmoothedNoise4D(int x, int y, int z, int w);
		float InterpolatedNoise4D(float x, float y, float z, float w);
		float PerlinNoise4D(float x, float y, float z, float w);
	};
}

#endif