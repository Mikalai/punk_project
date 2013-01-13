#ifndef _H_PUNK_PERLIN_NOISE
#define _H_PUNK_PERLIN_NOISE

#include <memory>
#include "../config.h"
#include "random.h"

namespace Math
{
	struct NoiseImpl;

	class PUNK_ENGINE Noise
	{
	public:

		Noise();
		Noise(unsigned seed);

		void SetOctavesCount(int value);
		void SetPersistance(double value);
		int GetOctavesCount() const;
		double GetPersistance() const;

		double Noise1D(int x);
		double SmoothedNoise1D(int x);
		double InterpolatedNoise1D(double x);
		double PerlinNoise1D(double x);

		double Noise2D(int x, int y);
		double SmoothedNoise2D(int x, int y);
		double InterpolatedNoise2D(double x, double y);
		double PerlinNoise2D(double x, double y);

		double Noise3D(int x, int y, int z);
		double SmoothedNoise3D(int x, int y, int z);
		double InterpolatedNoise3D(double x, double y, double z);
		double PerlinNoise3D(double x, double y, double z);

		double Noise4D(int x, int y, int z, int w);
		double SmoothedNoise4D(int x, int y, int z, int w);
		double InterpolatedNoise4D(double x, double y, double z, double w);
		double PerlinNoise4D(double x, double y, double z, double w);

		void GenerateHeightMap(double offset_x, double offset_y, double dim_x, double dim_y, int width, int height, float* data);

	private:		
		std::auto_ptr<NoiseImpl> impl;
	};
}

#endif