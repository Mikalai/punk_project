#ifndef _H_PUNK_FRUSTUM
#define _H_PUNK_FRUSTUM

#include "../config.h"
#include "mat4.h"
#include "plane.h"
#include "aabb.h"
#include "clip_space.h"

namespace Math
{
    enum class FrustumPlane : uint8_t;

	class PUNK_ENGINE_API Frustum
	{
	public:

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

        Frustum(const mat4& projection_matrix);

		//void Set(float left, float right, float top, float bottom, float znear, float zfar);
		//void Set(float fov, float width, float height, float near, float far);
        //void Set(float fov, float width, float height, float near, float far);
		const mat4& GetProjectionMatrix() const;
		const ClipSpace ToClipSpace() const;

        float GetFovY() const;
        float GetAspectRation() const;
        float GetNearPlane() const;
        float GetFarPlane() const;

		const Plane& GetPlane(FrustumPlane value) const;
		const Math::vec3& GetPoint(FrustumPoints value) const;

        //void Save(System::Buffer* buffer) const;
        //void Load(System::Buffer* buffer);

		static bool IsAdjacent(FrustumPlane a, FrustumPlane b);

        void Update();

	protected:

		Plane m_planes[6];

		Math::vec3 m_points[8];

        const mat4& m_projection_matrix;
//		float m_fov;
//		float m_aspect;
//		float m_znear;
//		float m_zfar;

        //void UpdateMatrix();
		void CalculatePlanes();
	};

    /**
      * Creates a clip space from current frustum and point.
      */
	PUNK_ENGINE_API const ClipSpace BuildClipSpaceFromPoint(const Frustum& f, const Math::vec3& p);
}

#endif
