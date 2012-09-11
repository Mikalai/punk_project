#ifndef _H_PUNK_FRUSTUM
#define _H_PUNK_FRUSTUM

#include "../config.h"
#include "mat4.h"
#include "plane.h"
#include "bounding_box.h"

namespace Math
{
	class PUNK_ENGINE Frustum
	{
	public:

		enum FrustumPlane {PLANE_TOP, PLANE_BOTTOM, PLANE_FAR, PLANE_NEAR, PLANE_LEFT, PLANE_RIGHT};
		enum CameraType {CAMERA_TARGET, CAMERA_FREE};
		enum Classification {OUTSIDE, INSIDE, INTERSECT};

	protected:

		Plane m_planes[6];

		mutable Matrix4x4<float> m_projection_matrix;
		mutable mat4 m_view_matrix;
		mutable mat4 m_projection_view_matrix;

		float m_fov;
		float m_aspect;
		float m_znear;
		float m_zfar;

		float m_near_width;
		float m_near_height;
		float m_far_width;
		float m_far_height;

		vec3 m_position;
		vec3 m_target;
		vec3 m_up;
		vec3 m_direction;

		CameraType m_type;

		void UpdateMatrix();
		void CalculatePlanes();

	public:

		Frustum();

		void SetProperties(float fov, float aspect, float near, float far);
		void SetPositionAndTarget(const vec3& position, const vec3& target, const vec3& up);
		void SetPositionAndDirection(const vec3& position, const vec3& direction, const vec3& up);
		void SetPosition(const vec3& position);
		void SetProjectionMatrix(const Math::mat4& matrix);

		Classification BoxInFrustum(const BoundingBox& m_bbox) const;

		const mat4& GetProjectionMatrix() const;
		const mat4& GetViewMatrix() const;
		const mat4& GetViewProjectionMatrix() const;
		const vec3& GetPosition() const;
	};
}

#endif