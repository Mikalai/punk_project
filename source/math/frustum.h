#ifndef _H_PUNK_FRUSTUM
#define _H_PUNK_FRUSTUM

#include "../config.h"
#include "mat4.h"
#include "plane.h"
#include "aabb.h"
#include "clip_space.h"

namespace Math
{
	class PUNK_ENGINE Frustum
	{
	public:

		enum FrustumPlane {PLANE_TOP, PLANE_BOTTOM, PLANE_LEFT, PLANE_RIGHT, PLANE_FAR, PLANE_NEAR};
		enum Classification {OUTSIDE, INSIDE, INTERSECT};

	public:

		Frustum();

		void Set(float left, float right, float top, float bottom, float znear, float zfar);
		//void Set(float fov, float width, float height, float near, float far);
		//void Set(float fov, float aspect, float near, float far);
		const mat4& GetProjectionMatrix() const;
		const ClipSpace ToClipSpace() const;

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

	protected:

		Plane m_planes[6];

		mat4 m_projection_matrix;
		float m_fov;
		float m_aspect;
		float m_znear;
		float m_zfar;	
		float m_left;
		float m_right;
		float m_top;
		float m_bottom;

		void UpdateMatrix();
		void CalculatePlanes();
	};
}

#endif