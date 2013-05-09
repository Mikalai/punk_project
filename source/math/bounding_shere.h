#ifndef _H_PUNK_MATH_BOUNDING_SPHERE
#define _H_PUNK_MATH_BOUNDING_SPHERE

#include "sphere.h"

namespace Math
{
	class BoundingSphere : public Sphere
	{
	public:
		BoundingSphere() {}
		BoundingSphere(const Sphere& s) : Sphere(s) {}
		bool Create(const float* vbuffer, int count, unsigned vertex_size);
	};

	inline const BoundingSphere operator * (const mat4& m, const BoundingSphere& bsphere)
	{
		BoundingSphere res;
        //  mat4 plane_matrix = m.Inversed().Transposed();
        //	mat3 normal_matrix = plane_matrix.RotationPart();

		res.SetCenter(m * bsphere.GetCenter());
		res.SetRadius(bsphere.GetRadius());
		return res;
	}
}

#endif	//	_H_PUNK_MATH_BOUNDING_SPHERE
