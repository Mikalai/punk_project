#include "terrain.h"

namespace Utility	
{

	Terrain::Terrain()
	{
		m_offset.Set(0,0,0);
		m_scale = 1.0;
		m_base_height = 0;
	}
	float Terrain::GetDistance(const Math::vec3& position)
	{
		Math::vec3 pos = position - m_offset;

		int u = (int)pos.X();
		int v = (int)pos.Z();

		if (u < 0 || v < 0 || u >= 2048 || v >= 2048)
			return 0;

		float height = (float)(GetHeightFromImage(u, v));

		height *= m_scale;
		height += m_base_height;
		
		return position.Y() - height;
	}

	int Terrain::GetHeightFromImage(int u, int v) const
	{
		if (m_landscape->GetComponentsCount() == 1)
		{
			int value = (int)(*m_landscape->GetPixelComponent(u, v, 1));
			return value;
		}
		else if (m_landscape->GetComponentsCount() == 3)
			return 255*255*(int)*m_landscape->GetPixelComponent(u, v, 0) + 255*(int)*m_landscape->GetPixelComponent(u, v, 1) + (int)*m_landscape->GetPixelComponent(u, v, 2);
		else if (m_landscape->GetComponentsCount() == 4)
			return 255*255*(int)*m_landscape->GetPixelComponent(u, v, 0) + 255*(int)*m_landscape->GetPixelComponent(u, v, 1) + (int)*m_landscape->GetPixelComponent(u, v, 2);
		
		throw System::SystemError(L"Can't get height from image");
	}

	void Terrain::SetHeightInImage(int x, int y, int height)
	{
		if (m_landscape->GetComponentsCount() == 1)
		{
			m_landscape->SetPixelComponent(x, y, 1, ImageModule::Component(height));
			return;
		}
		else if (m_landscape->GetComponentsCount() == 3)
		{
			ImageModule::Component zero = height / (255 * 255);
			height -= zero * 255 * 255;
			ImageModule::Component first = (height / 255) % 255;
			height -= first * 255;
			ImageModule::Component second = height;
			m_landscape->SetPixelComponent(x, y, 0, zero);
			m_landscape->SetPixelComponent(x, y, 1, first);
			m_landscape->SetPixelComponent(x, y, 2, second);
			return;
		}		
		else if (m_landscape->GetComponentsCount() == 4)
		{
			ImageModule::Component zero = height / (255 * 255);
			height -= zero * 255 * 255;
			ImageModule::Component first = (height / 255) % 255;
			height -= first * 255;
			ImageModule::Component second = height;
			m_landscape->SetPixelComponent(x, y, 0, zero);
			m_landscape->SetPixelComponent(x, y, 1, first);
			m_landscape->SetPixelComponent(x, y, 2, second);
			return;
		}
		throw System::SystemError(L"Can't set height in image");
	}

	float Terrain::GetHeight(float x, float z) const
	{		
	//	float scale = 1.0; //1.0 / 255.0;
		int u = (int)(x-1);
		int v = (int)(z);

		if (u < 0 || v < 0 || u >= 2048 || v >= 2048)
			return 0;

		//float du = x - u;
		//float dv = z - v;

		//x -= (du > 0.5 ? 0.5 : 0);
		//z -= (dv > 0.5 ? 0.5 : 0);

		//	bilinear interpolation goes here
		float hp00 = m_scale*(float)(GetHeightFromImage(u, v));
		float hp10 = m_scale*(float)(GetHeightFromImage(u-1, v));
		float hp01 = m_scale*(float)(GetHeightFromImage(u, v-1));
		float hp11 = m_scale*(float)(GetHeightFromImage(u-1, v-1));

		float wx = 0.5f+(x - int(x));
		float wz = 0.5f+(z - int(z));

		float hx1 = hp10*(1-wx) + hp00*(wx);
		float hx2 = hp11*(1-wx) + hp01*(wx);
		float h = hx2*(1-wz) + hx1*(wz);
		h += m_base_height;
		return h;
	}

	void Terrain::SetHeight(float x, float z, float height)
	{
		float dx = x - int(x);
		float dz = z - int(z);
		int xx = (int)x;
		int zz = (int)z;
		SetHeightInImage((int)(xx), (int)(zz), int(height / m_scale));
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
				float dst = GetDistance(out);
				if (dst < 0)
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