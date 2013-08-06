#ifndef _H_PUNK_MATH_BOUNDING_BOX
#define _H_PUNK_MATH_BOUNDING_BOX

#include <vector>
#include "../config.h"
#include "vec3.h"
#include "plane.h"
#include "bounding_shere.h"

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
        void Save(System::Buffer* buffer) const;
        void Load(System::Buffer* buffer);

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
	};

	inline const BoundingBox operator * (const mat4& m, const BoundingBox& bbox)
	{
		BoundingBox res;
		mat4 plane_matrix = m.Inversed().Transposed();
		mat3 normal_matrix = plane_matrix.RotationPart();

		res.m_center_of_mass = m * bbox.m_center_of_mass;
		res.m_center = m * bbox.m_center;
		res.m_r = normal_matrix * bbox.m_r;
		res.m_s = normal_matrix * bbox.m_s;
		res.m_t = normal_matrix * bbox.m_t;

		for (int i = 0; i < 6; ++i)
		{
			res.m_plane[i] = plane_matrix * bbox.m_plane[i];
		}

		return res;
	}
}

#endif	//	_H_PUNK_MATH_BOUNDING_BOX
