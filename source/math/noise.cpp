#include <noise/noise.h>
#include <time.h>
#include "noise.h"
#include "constants.h"
#include "interpolation.h"
#include "noiseutils.h"

namespace Math
{
	struct NoiseImpl
	{
		noise::module::Perlin m_perlin;
		Random m_rnd;

		NoiseImpl()
		{
			time_t t;
			time(&t);
			m_rnd.SetSeed(t);
			m_perlin.SetSeed(t);
			m_perlin.SetOctaveCount(4);
			m_perlin.SetPersistence(0.25);
		}

		NoiseImpl(int seed)
		{
			m_rnd.SetSeed(seed);
			m_perlin.SetSeed(seed);
			m_perlin.SetOctaveCount(4);
			m_perlin.SetPersistence(0.25);
		}
	};

	Noise::Noise() : impl(new NoiseImpl)
	{
	}

	Noise::Noise(unsigned seed) : impl(new NoiseImpl(seed))
	{
	}

	double Noise::Noise1D(int x)
	{		
		impl->m_rnd.SetSeed(impl->m_rnd.Noise(x)*100000.0);
		return impl->m_rnd.Uniform(-1.0, 1.0);
	}

	double Noise::SmoothedNoise1D(int x)
	{
		return Noise1D(x) / 2.0f + Noise1D(x-1)/4.0f + Noise1D(x+1)/4.0f;
	}

	double Noise::InterpolatedNoise1D(double x)
	{		
		int int_x = int(x);

		double frac = x - int_x;

		double v1 = SmoothedNoise1D(int_x);
		double v2 = SmoothedNoise1D(int_x + 1);

		return cosine_interpolation(v1, v2, frac);
	}

	double Noise::PerlinNoise1D(double x)
	{
		return impl->m_perlin.GetValue(x, 0, 0);
		//double total = 0;
		//double p = m_persistence;
		//
		//for (int i = 0; i < m_max_octaves; i++)
		//{
		//	double freq = pow(2, (double)i);
		//	double amp = pow(p, (double)i);

		//	total += InterpolatedNoise1D(x * freq) * amp;
		//}		
		//return total;
	}

	double Noise::Noise2D(int x, int y)
	{
		x += 57 * y;
		impl->m_rnd.SetSeed(impl->m_rnd.Noise(x)*100000.0);
		return impl->m_rnd.Uniform(-1.0, 1.0);
	}

	double Noise::SmoothedNoise2D(int x, int y)
	{
		double corner = (Noise2D(x-1, y-1) + Noise2D(x+1, y-1) + Noise2D(x-1, y+1) + Noise2D(x+1, y+1)) / 16.0f;
		double sides = (Noise2D(x-1, y) + Noise2D(x+1, y) + Noise2D(x, y-1) + Noise2D(x, y+1)) / 8.0f;
		double center = Noise2D(x,y) / 4.0f;
		return corner + sides + center;
	}

	double Noise::InterpolatedNoise2D(double x, double y)
	{
		int int_x = int(x);
		double frac_x = x - int_x;

		int int_y = int(y);
		double frac_y = y - int_y;

		double v1 = SmoothedNoise2D(int_x, int_y);
		double v2 = SmoothedNoise2D(int_x+1, int_y);
		double v3 = SmoothedNoise2D(int_x, int_y+1);
		double v4 = SmoothedNoise2D(int_x+1, int_y+1);

		double i1 = cosine_interpolation(v1, v2, frac_x);
		double i2 = cosine_interpolation(v3, v4, frac_x);

		return cosine_interpolation(i1, i2, frac_y);
	}

	double Noise::PerlinNoise2D(double x, double y)
	{
		return impl->m_perlin.GetValue(x, y, 2);
		/*double total = 0;
		double p = m_persistence;
		
		for (int i = 0; i < m_max_octaves; i++)
		{
			double freq = pow(2, (double)i);
			double amp = pow(p, (double)i);

			total += InterpolatedNoise2D(x * freq, y * freq) * amp;
		}		
		return total;*/
	}

	double Noise::Noise3D(int x, int y, int z)
	{
		x += 57 * y + 131 * z;		
		impl->m_rnd.SetSeed(impl->m_rnd.Noise(x)*100000.0);
		return impl->m_rnd.Uniform(-1.0, 1.0);
	}

	double Noise::SmoothedNoise3D(int x, int y, int z)
	{
		double diag_corner = (Noise3D(x-1, y-1, z-1) + Noise3D(x-1, y+1, z-1) + Noise3D(x+1, y+1, z-1) + Noise3D(x+1, y-1, z-1)
			+ Noise3D(x-1, y-1, z+1) + Noise3D(x-1, y+1, z+1) + Noise3D(x+1, y+1, z+1) + Noise3D(x+1, y-1, z+1)) / 32.0f;
		
		double corner = (Noise3D(x-1, y-1, z) + Noise3D(x+1, y-1, z) + Noise3D(x-1, y+1, z) + Noise3D(x+1, y+1, z) +
			Noise3D(x, y-1, z-1) + Noise3D(x, y-1, z+1) + Noise3D(x, y+1, z-1) + Noise3D(x, y+1, z+1) +
			Noise3D(x-1, y, z-1) + Noise3D(x+1, y, z-1) + Noise3D(x-1, y, z+1) + Noise3D(x+1, y, z+1)) / 16.0f;

		double sides = (Noise3D(x-1, y, z) + Noise3D(x+1, y, z) + Noise3D(x, y-1, z) + Noise3D(x, y+1, z) + Noise3D(x, y, z-1) + Noise3D(x, y, z + 1)) / 8.0f;
		double center = Noise3D(x,y,z) / 4.0f;
		return corner + sides + center + diag_corner;
	}

	double Noise::InterpolatedNoise3D(double x, double y, double z)
	{
		int int_x = int(x);
		double frac_x = x - int_x;

		int int_y = int(y);
		double frac_y = y - int_y;

		int int_z = int(z);
		double frac_z = z - int_z;

		double v1 = SmoothedNoise3D(int_x, int_y, int_z);
		double v2 = SmoothedNoise3D(int_x+1, int_y, int_z);
		double v3 = SmoothedNoise3D(int_x, int_y+1, int_z);
		double v4 = SmoothedNoise3D(int_x+1, int_y+1, int_z);
		
		double v5 = SmoothedNoise3D(int_x, int_y, int_z+1);
		double v6 = SmoothedNoise3D(int_x+1, int_y, int_z+1);
		double v7 = SmoothedNoise3D(int_x, int_y+1, int_z+1);
		double v8 = SmoothedNoise3D(int_x+1, int_y+1, int_z+1);

		double i1 = cosine_interpolation(v1, v2, frac_x);
		double i2 = cosine_interpolation(v3, v4, frac_x);
		double i3 = cosine_interpolation(v5, v6, frac_x);
		double i4 = cosine_interpolation(v7, v8, frac_x);

		double ii1 = cosine_interpolation(i1, i2, frac_y);
		double ii2 = cosine_interpolation(i3, i4, frac_y);

		return cosine_interpolation(ii1, ii2, frac_z);
	}

	double Noise::PerlinNoise3D(double x, double y, double z)
	{
		return impl->m_perlin.GetValue(x, y, z);
		//double total = 0;
		//double p = m_persistence;
		//
		//for (int i = 0; i < m_max_octaves; i++)
		//{
		//	double freq = pow(2, (double)i);
		//	double amp = pow(p, (double)i);

		//	total += InterpolatedNoise3D(x * freq, y * freq, z * freq) * amp;
		//}		
		//return total;
	}

	void Noise::SetOctavesCount(int count)
	{
		impl->m_perlin.SetOctaveCount(count);
	}

	void Noise::SetPersistance(double value)
	{
		impl->m_perlin.SetPersistence(value);
	}

	int Noise::GetOctavesCount() const
	{
		return impl->m_perlin.GetOctaveCount();
	}

	double Noise::GetPersistance() const
	{
		return impl->m_perlin.GetPersistence();
	}

	void Noise::GenerateHeightMap(double offset_x, double offset_y, double dim_x, double dim_y, int width, int height, float* data)
	{
		utils::NoiseMap heightMap;
		utils::NoiseMapBuilderPlane heightMapBuilder;
		heightMapBuilder.SetSourceModule(impl->m_perlin);
		heightMapBuilder.SetDestNoiseMap(heightMap);
		heightMapBuilder.SetDestSize(width, height);
		heightMapBuilder.SetBounds(offset_x, offset_x + dim_x, offset_y, offset_y + dim_y);
		heightMapBuilder.Build();
	
		memcpy(data, heightMap.GetSlabPtr(), width*height*sizeof(float));

	}
}