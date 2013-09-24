#ifndef _H_PUNK_MATH_BOUNDING_SPHERE
#define _H_PUNK_MATH_BOUNDING_SPHERE

#include <vector>
#include "sphere.h"

namespace Math
{
	class BoundingSphere : public Sphere
	{
	public:
		BoundingSphere() {}
		BoundingSphere(const Sphere& s) : Sphere(s) {}
        bool Create(const std::vector<vec3>& vbuffer);

        friend void SaveBoundingSphere(System::Buffer* buffer, const BoundingSphere& sphere);
        friend void LoadBoundingSphere(System::Buffer* buffer, BoundingSphere& sphere);
	};

    PUNK_ENGINE_API void SaveBoundingSphere(System::Buffer* buffer, const BoundingSphere& sphere);
    PUNK_ENGINE_API void LoadBoundingSphere(System::Buffer* buffer, BoundingSphere& sphere);
    PUNK_ENGINE_API const BoundingSphere operator * (const mat4& m, const BoundingSphere& bsphere);
}

#endif	//	_H_PUNK_MATH_BOUNDING_SPHERE
