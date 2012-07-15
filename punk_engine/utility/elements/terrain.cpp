#include "terrain.h"

namespace Utility	
{
	float Terrain::GetDistance(const Math::vec3& position)
	{
		float scale = 1.0;

		Math::vec3 pos = position - m_offset;

		int u = pos.X();
		int v = pos.Z();

		if (u < 0 || v < 0 || u >= 2048 || v >= 2048)
			return 0;

		float height = (float)(*m_landscape->GetPixelComponent(u, v, 1)) * scale;

		height *= m_scale;
		height += m_base_height;
		
		return position.Y() - height;
	}

	float Terrain::GetHeight(float x, float z) const
	{		
		float scale = 1.0; //1.0 / 255.0;
		int u = x;
		int v = z;

		if (u < 0 || v < 0 || u >= 2048 || v >= 2048)
			return 0;

		//	bilinear interpolation goes here
		float hp00 = m_scale*(float)(*m_landscape->GetPixelComponent(u, v, 1)) * scale;
		float hp10 = m_scale*(float)(*m_landscape->GetPixelComponent(u+1, v, 1)) * scale;
		float hp01 = m_scale*(float)(*m_landscape->GetPixelComponent(u, v+1, 1)) * scale;
		float hp11 = m_scale*(float)(*m_landscape->GetPixelComponent(u+1, v+1, 1)) * scale;

		float wx = x - u;
		float wz = z - v;

		float hx1 = hp10*wx + hp00*(1-wx);
		float hx2 = hp11*wx + hp01*(1-wx);
		float h = hx2*wz + hx1*(1-wz);
		h += m_base_height;
		return h;
	}

	void Terrain::SetHeight(float x, float z, float height)
	{
		if (height > 255)
			height = 255;
		float scale = 1.0f; //255.0f;
		*m_landscape->GetPixelComponent(x, z, 1) = height * scale;
		m_modified = true;
	}

	bool Terrain::IntersectWithRay(const Math::vec3& start, const Math::vec3& dir, Math::vec3& out)
	{
		out = start;
		float delta = 1;		
		bool was_found = false;
		while (delta > 0.01)
		{
			for (int i = 0; i < 1000; i++)
			{
				out += dir * delta;
				if (GetDistance(out) < 0)
				{
					out -= dir * delta;
					was_found = true;
					break;
				}
			}
			if (!was_found)
				return false;
			delta /= 10.0f;
		}
		return true;
	}
}