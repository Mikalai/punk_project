#include "helper.h"
#include "bounding_shere.h"

namespace Math
{
    bool BoundingSphere::Create(const std::vector<vec3>& vbuffer)
	{
        if (vbuffer.empty())
			return (out_error() << "Bad data to counstruct bounding sphere" << std::endl, false);

		vec3 r, s, t;
        if (!CalculateNativeAxis(vbuffer, r, s, t))
			return (out_error() << "Can't build bounding sphere" << std::endl, false);

        vec3 min_p = vbuffer.front();
		float min_value = r.Dot(min_p);
		vec3 max_p = min_p;
		float max_value = r.Dot(max_p);

        for (auto v : vbuffer)
		{		
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
