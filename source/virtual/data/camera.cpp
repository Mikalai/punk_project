#include "camera.h"
#include "../../math/helper.h"
#include "../../math/frustum.h"

namespace Virtual
{
	Camera::Camera()
	{
	}

	Camera::Camera(const CameraOptions& options)
	{
		m_frustum.Set(-1, 1, options.m_aspect, -options.m_aspect, options.m_near, options.m_far);			
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
		std::ifstream stream(path.Data(), std::ios::binary);
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
}