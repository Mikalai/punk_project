#ifndef _H_PUNK_MATH_BOUNDING_SPHERE
#define _H_PUNK_MATH_BOUNDING_SPHERE

#include "sphere.h"

namespace Math
{
	class BoundingSphere : public Sphere
	{
	public:
		bool Create(const float* vbuffer, int count, unsigned vertex_size);
	};
}

#endif	//	_H_PUNK_MATH_BOUNDING_SPHERE