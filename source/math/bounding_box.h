#ifndef _H_PUNK_MATH_BOUNDING_BOX
#define _H_PUNK_MATH_BOUNDING_BOX

#include <vector>
#include "../config.h"
#include "vec3.h"
#include "plane.h"
#include "bounding_sphere.h"

namespace Math
{
	class PUNK_ENGINE_API BoundingBox
	{
	public:

		/**
		*	Initialize bounding box with array of vertex
		*/
        bool Create(const std::vector<vec3>& vbuffer);

		const vec3& GetR() const { return m_r; }
		const vec3& GetS() const { return m_s; }
		const vec3& GetT() const { return m_t; }
		const vec3& GetCenter() const { return m_center; }
		const vec3& GetMassCenter() const { return m_center_of_mass; }
        const vec3& GetMinCorner() const { return m_min_corner; }
		const Plane& GetPlane(int index) const { return m_plane[index]; }
        const BoundingSphere ToBoundingSphere();
	private:

		//	natural center
		vec3 m_center_of_mass;
		
		//	bbox center
		vec3 m_center;
        vec3 m_min_corner;

		//	natural axes
		vec3 m_r;
		vec3 m_s;
		vec3 m_t;

		//	natural planes of the bbox 
		Plane m_plane[6];

		friend const BoundingBox operator * (const mat4& m, const BoundingBox& bbox);
        friend void SaveBoundingBox(System::Buffer* buffer, const BoundingBox& value);
        friend void LoadBoundingBox(System::Buffer* buffer, BoundingBox& value);
	};

    PUNK_ENGINE_API const BoundingBox operator * (const mat4& m, const BoundingBox& bbox);
    PUNK_ENGINE_API void SaveBoundingBox(System::Buffer* buffer, const BoundingBox& value);
    PUNK_ENGINE_API void LoadBoundingBox(System::Buffer* buffer, BoundingBox& value);

}

#endif	//	_H_PUNK_MATH_BOUNDING_BOX
