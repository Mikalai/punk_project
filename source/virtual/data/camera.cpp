#include "camera.h"
#include "../../math/helper.h"
#include "../../math/frustum.h"
#include "../../math/line3d.h"

namespace Virtual
{
	Camera::Camera()
	{
	}

	Camera::Camera(const CameraOptions& options)
	{
		m_frustum.Set(options.m_fov, 1, 3.0 / 4.0, options.m_near, options.m_far);
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

	const Math::mat4 Camera::GetProjectionMatrix() const
	{
		return m_frustum.GetProjectionMatrix();
	}

	const Math::mat4 Camera::GetViewMatrix() const
	{
		return m_view_matrix;
	}

	const Math::ClipSpace Camera::ToClipSpace() const
	{
		return m_frustum.ToClipSpace();
	}

	void Camera::SetPosition(const Math::vec3& pos)
	{
		m_position = pos;
		UpdateInternals();
	}

	bool Camera::Save(std::ostream& stream) const
	{
		m_frustum.Save(stream);
		return true;
	}

	bool Camera::Load(std::istream& stream)
	{
		m_frustum.Load(stream);
		return true;
	}

	void Camera::UpdateInternals()
	{
		Math::YawPitchRollToUpDirection(m_yrp[0], m_yrp[1], m_yrp[2], m_up, m_direction);
		m_right = m_direction.Cross(m_up);
		m_view_matrix = Math::mat4::CreateTargetCameraMatrix(m_position, m_position + m_direction, m_up);
	}

	Camera* Camera::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	Camera* Camera::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<Camera> node(new Camera);
		node->Load(stream);
		return node.release();
	}

	const Math::Line3D Camera::GetWorldRay(float x, float y)
	{
		//	aspect ratio as used in opengl
		float aspect = m_viewport.GetWidth() / m_viewport.GetHeight();
		//	translate x and y to projection plane
		float proj_x = aspect*(-1.0f + 2.0f * (float)x / m_viewport.GetWidth());
		float proj_y = -1.0f + 2.0f * (float)(m_viewport.GetHeight() - y) / m_viewport.GetHeight();


		//	find mouse point in the view space
		Math::vec3 mouse_in_view(proj_x, proj_y, -1.0f / tan(m_frustum.GetFOV()/2.0f));
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
