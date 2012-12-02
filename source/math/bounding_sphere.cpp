#include "helper.h"
#include "bounding_shere.h"

namespace Math
{
	bool BoundingSphere::Create(const float* vbuffer, int count, unsigned vertex_size)
	{
		if (vbuffer == nullptr || count == 0 || vertex_size == 0)
			return (out_error() << "Bad data to counstruct bounding sphere" << std::endl, false);

		vec3 r, s, t;
		if (!CalculateNativeAxis(vbuffer, count, vertex_size, r, s, t))
			return (out_error() << "Can't build bounding sphere" << std::endl, false);

		vec3 min_p = vec3(vbuffer[0], vbuffer[1], vbuffer[2]);
		float min_value = r.Dot(min_p);
		vec3 max_p = min_p;
		float max_value = r.Dot(max_p);

		for (int i = 0; i < count; ++i)
		{
			const vec3 v(vbuffer[i*(vertex_size/sizeof(float)) + 0], vbuffer[i*(vertex_size/sizeof(float)) + 1], vbuffer[i*(vertex_size/sizeof(float)) + 2]);
		
			float value = r.Dot(v);
			if (min_value > value)
			{
				min_p = v;
				min_value = value;
			}
			
			if (max_value < value)
			{
				max_p = v;
				max_value = value;
			}
		}

		const vec3 q = (min_p + max_p) / 2.0f;
		float radius = (min_p - q).Length();

		SetCenter(q);
		SetRadius(radius);

		return true;
	}
}