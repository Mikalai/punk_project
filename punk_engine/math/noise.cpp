#include "noise.h"
#include "constants.h"
#include "interpolation.h"
#include "random.h"

namespace Math
{
	Noise::Noise() : m_persistence(0.25), m_max_octaves(4)
	{
	}

	float Noise::Noise1D(int x)
	{
		Random rnd;
		return rnd.Uniform(x, 0.0f, 1.0f);
	}

	float Noise::SmoothedNoise1D(int x)
	{
		return Noise1D(x) / 2.0f + Noise1D(x-1)/4.0f + Noise1D(x+1)/4.0f;
	}

	float Noise::InterpolatedNoise1D(float x)
	{		
		int int_x = int(x);

		float frac = x - int_x;

		float v1 = SmoothedNoise1D(int_x);
		float v2 = SmoothedNoise1D(int_x + 1);

		return cosine_interpolation(v1, v2, frac);
	}

	float Noise::PerlinNoise1D(float x)
	{
		float total = 0;
		float p = m_persistence;
		
		for (int i = 0; i < m_max_octaves; i++)
		{
			float freq = powf(2, (float)i);
			float amp = powf(p, (float)i);

			total += InterpolatedNoise1D(x * freq) * amp;
		}		
		return total;
	}

	float Noise::Noise2D(int x, int y)
	{
		x += 57 * y;
		Random rnd;
		return rnd.UniformNormalized(x);
	}

	float Noise::SmoothedNoise2D(int x, int y)
	{
		float corner = (Noise2D(x-1, y-1) + Noise2D(x-1, y+1) + Noise2D(x+1, y+1) + Noise2D(x+1, y-1)) / 16.0f;
		float sides = (Noise2D(x-1, y) + Noise2D(x+1, y) + Noise2D(x, y-1) + Noise2D(x, y+1)) / 8.0f;
		float center = Noise2D(x,y) / 4.0f;
		return corner + sides + center;
	}

	float Noise::InterpolatedNoise2D(float x, float y)
	{
		int int_x = int(x);
		float frac_x = x - int_x;

		int int_y = int(y);
		float frac_y = y - int_y;

		float v1 = SmoothedNoise2D(int_x, int_y);
		float v2 = SmoothedNoise2D(int_x+1, int_y);
		float v3 = SmoothedNoise2D(int_x, int_y+1);
		float v4 = SmoothedNoise2D(int_x+1, int_y+1);

		float i1 = cosine_interpolation(v1, v2, frac_x);
		float i2 = cosine_interpolation(v3, v4, frac_x);

		return cosine_interpolation(i1, i2, frac_y);
	}

	float Noise::PerlinNoise2D(float x, float y)
	{
		float total = 0;
		float p = m_persistence;
		
		for (int i = 0; i < m_max_octaves; i++)
		{
			float freq = powf(2, (float)i);
			float amp = powf(p, (float)i);

			total += InterpolatedNoise2D(x * freq, y * freq) * amp;
		}		
		return total;
	}

	float Noise::Noise3D(int x, int y, int z)
	{
		x += 57 * y + 131 * z;
		Random rnd;
		return rnd.Uniform(x, 0.0f, 1.0f);
	}

	float Noise::SmoothedNoise3D(int x, int y, int z)
	{
		float diag_corner = (Noise3D(x-1, y-1, z-1) + Noise3D(x-1, y+1, z-1) + Noise3D(x+1, y+1, z-1) + Noise3D(x+1, y-1, z-1)
			+ Noise3D(x-1, y-1, z+1) + Noise3D(x-1, y+1, z+1) + Noise3D(x+1, y+1, z+1) + Noise3D(x+1, y-1, z+1)) / 32.0f;
		
		float corner = (Noise3D(x-1, y-1, z) + Noise3D(x+1, y-1, z) + Noise3D(x-1, y+1, z) + Noise3D(x+1, y+1, z) +
			Noise3D(x, y-1, z-1) + Noise3D(x, y-1, z+1) + Noise3D(x, y+1, z-1) + Noise3D(x, y+1, z+1) +
			Noise3D(x-1, y, z-1) + Noise3D(x+1, y, z-1) + Noise3D(x-1, y, z+1) + Noise3D(x+1, y, z+1)) / 16.0f;

		float sides = (Noise3D(x-1, y, z) + Noise3D(x+1, y, z) + Noise3D(x, y-1, z) + Noise3D(x, y+1, z) + Noise3D(x, y, z-1) + Noise3D(x, y, z + 1)) / 8.0f;
		float center = Noise3D(x,y,z) / 4.0f;
		return corner + sides + center + diag_corner;
	}

	float Noise::InterpolatedNoise3D(float x, float y, float z)
	{
		int int_x = int(x);
		float frac_x = x - int_x;

		int int_y = int(y);
		float frac_y = y - int_y;

		int int_z = int(z);
		float frac_z = z - int_z;

		float v1 = SmoothedNoise3D(int_x, int_y, int_z);
		float v2 = SmoothedNoise3D(int_x+1, int_y, int_z);
		float v3 = SmoothedNoise3D(int_x, int_y+1, int_z);
		float v4 = SmoothedNoise3D(int_x+1, int_y+1, int_z);
		
		float v5 = SmoothedNoise3D(int_x, int_y, int_z+1);
		float v6 = SmoothedNoise3D(int_x+1, int_y, int_z+1);
		float v7 = SmoothedNoise3D(int_x, int_y+1, int_z+1);
		float v8 = SmoothedNoise3D(int_x+1, int_y+1, int_z+1);

		float i1 = cosine_interpolation(v1, v2, frac_x);
		float i2 = cosine_interpolation(v3, v4, frac_x);
		float i3 = cosine_interpolation(v5, v6, frac_x);
		float i4 = cosine_interpolation(v7, v8, frac_x);

		float ii1 = cosine_interpolation(i1, i2, frac_y);
		float ii2 = cosine_interpolation(i3, i4, frac_y);

		return cosine_interpolation(ii1, ii2, frac_z);
	}

	float Noise::PerlinNoise3D(float x, float y, float z)
	{
		float total = 0;
		float p = m_persistence;
		
		for (int i = 0; i < m_max_octaves; i++)
		{
			float freq = powf(2, (float)i);
			float amp = powf(p, (float)i);

			total += InterpolatedNoise3D(x * freq, y * freq, z * freq) * amp;
		}		
		return total;
	}

	void Noise::SetOctavesCount(int count)
	{
		m_max_octaves = count;
	}

	void Noise::SetPersistance(float value)
	{
		m_persistence = value;
	}

	int Noise::GetOctavesCount() const
	{
		return m_max_octaves;
	}

	float Noise::GetPersistance() const
	{
		return m_persistence;
	}
}