#ifndef _H_PUNK_CAMERA
#define _H_PUNK_CAMERA

#include "../../config.h"
#include "../../math/mat4.h"
#include "../../math/frustum.h"
#include "../../math/constants.h"
#include "../../math/rect.h"
//#include "../../system/object.h"
#include "entity.h"

namespace Utility { class CameraDesc; }

namespace Virtual
{
	struct PUNK_ENGINE_API CameraOptions 
	{
		float m_near;
		float m_far;
		float m_fov;
		float m_aspect;

		CameraOptions()
			: m_near(1.0f)
			, m_far(1000.0f)
			, m_fov(Math::PI/4.0f)
			, m_aspect(1.6f)
		{}
	};

	class PUNK_ENGINE_API Camera : public System::Object
	{
	public:
		Camera();
		Camera(const CameraOptions& options);
		void SetPosition(const Math::vec3& pos);
        void SetPosition(float x, float y, float z);
		const Math::vec3& GetPosition() const { return m_position; }
		Math::vec3& GetPosition() { return m_position; }
		const Math::mat4 GetProjectionMatrix() const;
		const Math::mat4 GetViewMatrix() const;
		const Math::vec3 GetDirection() const { return m_direction; }
		const Math::vec3 GetUpVector() const { return m_up; }
		const Math::ClipSpace ToClipSpace() const;

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

		Camera* CreateFromFile(const System::string& path);
		Camera* CreateFromStream(std::istream& stream);

		void SetYaw(float value);
		void SetRoll(float value);
		void SetPitch(float value);

		void SetYawRollPitch(float yaw, float roll, float pitch);
		void SetYawRollPitch(const Math::vec3& yrp);

		const Math::vec3& GetYawRollPitch() const { return m_yrp; }
		float GetYaw() const { return m_yrp[0]; }
		float GetRoll() const { return m_yrp[1]; }
		float GetPitch() const { return m_yrp[2]; }

		const Math::vec3& GetRightVector() const { return m_right; }

		Math::Frustum& GetFrustum() { return m_frustum; }
		const Math::Frustum& GetFrustum() const { return m_frustum; }

		const Math::Rect& GetViewport() const { return m_viewport; }
		void SetViewport(float x, float y, float width, float height) { m_viewport.Set(x, y, width, height); }

		const Math::Line3D GetWorldRay(float view_x, float view_y);
	private:
		Math::vec3 m_yrp;	//	yaw roll pitch
		Math::vec3 m_position;
		Math::vec3 m_direction;
		Math::vec3 m_right;
		Math::vec3 m_up;
		Math::mat4 m_view_matrix;
        Math::mat4 m_proj_matrix;
		Math::Frustum m_frustum;
		Math::Rect m_viewport;

		void UpdateInternals();
	};
}

#endif
