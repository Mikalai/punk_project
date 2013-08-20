#include "camera.h"
#include "../../math/helper.h"
#include "../../math/frustum.h"
#include "../../math/line3d.h"

namespace Virtual
{
	Camera::Camera()
        : m_yrp(0, 0, 0)
        , m_position(0, 0, 0)
	{
        UpdateInternals();
	}

	Camera::Camera(const CameraOptions& options)
        : m_yrp(0, 0, 0)
        , m_position(0, 0, 0)
	{
        m_proj_matrix = Math::mat4::CreatePerspectiveProjection(options.m_fov, 1, options.m_aspect, options.m_near, options.m_far);
        //m_frustum.Update();
	}

	void Camera::SetYaw(float value)
	{
		m_yrp[0] = value;
		UpdateInternals();
	}

	void Camera::SetRoll(float value)
	{
		m_yrp[1] = value;
		UpdateInternals();
	}

	void Camera::SetPitch(float value)
	{
		m_yrp[2] = value;
		UpdateInternals();
	}

	void Camera::SetYawRollPitch(float yaw, float roll, float pitch)
	{
		m_yrp.Set(yaw, roll, pitch);
		UpdateInternals();
	}

	void Camera::SetYawRollPitch(const Math::vec3& yrp)
	{
		m_yrp = yrp;
		UpdateInternals();
	}

    const Math::mat4 Camera::GetProjectionMatrix()
	{
        return Math::FrustumCreatePerspectiveProjectionMatrix(m_frustum);
	}

	const Math::mat4 Camera::GetViewMatrix() const
	{
		return m_view_matrix;
	}

	const Math::ClipSpace Camera::ToClipSpace() const
	{
        return Math::FrustumToClipSpace(m_frustum);
	}

	void Camera::SetPosition(const Math::vec3& pos)
	{
		m_position = pos;
		UpdateInternals();
	}

    void Camera::SetPosition(float x, float y, float z)
    {
        m_position.Set(x, y, z);
        UpdateInternals();;
    }

    void Camera::Save(System::Buffer *buffer) const
	{        
	}

    void Camera::Load(System::Buffer *buffer)
	{

	}

	void Camera::UpdateInternals()
	{
		Math::YawPitchRollToUpDirection(m_yrp[0], m_yrp[1], m_yrp[2], m_up, m_direction);
		m_right = m_direction.Cross(m_up);
		m_view_matrix = Math::mat4::CreateTargetCameraMatrix(m_position, m_position + m_direction, m_up);
	}

//	Camera* Camera::CreateFromFile(const System::string& path)
//	{
//		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
//		if (!stream.is_open())
//			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
//		return CreateFromStream(stream);
//	}

	const Math::Line3D Camera::GetWorldRay(float x, float y)
	{
		//	aspect ratio as used in opengl
		float aspect = m_viewport.GetWidth() / m_viewport.GetHeight();
		//	translate x and y to projection plane
		float proj_x = aspect*(-1.0f + 2.0f * (float)x / m_viewport.GetWidth());
		float proj_y = -1.0f + 2.0f * (float)(m_viewport.GetHeight() - y) / m_viewport.GetHeight();


		//	find mouse point in the view space
        Math::vec3 mouse_in_view(proj_x, proj_y, -1.0f / tan(m_frustum.fov/2.0f));
		//	translate mouse point to the world space
		Math::vec4 mouse_in_world_4 = (m_view_matrix.Inversed() * Math::vec4(mouse_in_view, 1.0f));
		mouse_in_world_4 /= mouse_in_world_4[3];
		Math::vec3 mouse_in_world = mouse_in_world_4.XYZ();
		//m_mouse_world = mouse_in_world;
		//	translate view center to the world
		Math::vec3 view_pos((m_view_matrix.Inversed() * Math::vec4(0,0,0, 1.0f)).XYZ());

		//	create a ray to intersect everything with it
		Math::Line3D ray;
		ray.SetOriginDestination(view_pos, mouse_in_world);
		return ray;
	}
}
