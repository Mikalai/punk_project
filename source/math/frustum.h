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

		enum FrustumPlane {
			PLANE_TOP,
			PLANE_BOTTOM,
			PLANE_LEFT,
			PLANE_RIGHT,
			PLANE_FAR,
			PLANE_NEAR
		};

		/**
		 * @brief The FrustumPoints enum. Contains corner points of the frustum.
		 */
		enum FrustumPoints {
			NLT, //!< Near left top
			NLB, //!< Near right bottom
			NRB, //!< Near right top
			NRT, //!< Near right top
			FLT, //!< Far left top
			FLB, //!< Far left bottom
			FRB, //!< Far right bottom
			FRT	 //!< Far right top
		};

		enum Classification {OUTSIDE, INSIDE, INTERSECT};

	public:

		Frustum();

		//void Set(float left, float right, float top, float bottom, float znear, float zfar);
		//void Set(float fov, float width, float height, float near, float far);
		void Set(float fov, float width, float height, float near, float far);
		const mat4& GetProjectionMatrix() const;
		const ClipSpace ToClipSpace() const;

		float GetFOV() const { return m_fov; }
		float GetAspectRation() const { return m_aspect; }
		float GetNearPlane() const { return m_znear; }
		float GetFarPlane() const { return m_zfar; }

		const Plane& GetPlane(FrustumPlane value) const;
		const Math::vec3& GetPoint(FrustumPoints value) const;

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

		static bool IsAdjacent(FrustumPlane a, FrustumPlane b);

	protected:

		Plane m_planes[6];

		Math::vec3 m_points[8];

		mat4 m_projection_matrix;
		float m_fov;
		float m_aspect;
		float m_znear;
		float m_zfar;	

		void UpdateMatrix();
		void CalculatePlanes();
	};

    /**
      * Creates a clip space from current frustum and point.
      */
	PUNK_ENGINE const ClipSpace BuildClipSpaceFromPoint(const Frustum& f, const Math::vec3& p);
}

#endif
