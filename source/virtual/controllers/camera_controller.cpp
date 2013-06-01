#include "camera_controller.h"
#include "../data/camera.h"

namespace Virtual
{
	CameraController::CameraController(Camera* camera)
		: m_camera(camera)
	{}

	void CameraController::MoveRight(float offset)
	{
		m_camera->SetPosition(m_camera->GetPosition() + m_camera->GetRightVector() * offset);		
	}

	void CameraController::MoveLeft(float offset)
	{
		m_camera->SetPosition(m_camera->GetPosition() + m_camera->GetRightVector() * -offset);
	}

	void CameraController::MoveForward(float offset)
	{
		m_camera->SetPosition(m_camera->GetPosition() + m_camera->GetDirection() * offset);
	}

	void CameraController::MoveBackward(float offset)
	{
		m_camera->SetPosition(m_camera->GetPosition() + m_camera->GetDirection() * -offset);
	}

	void CameraController::MoveAlongWorldAxisX(float offset)
	{
		auto& v = m_camera->GetPosition();
		v[0] += offset;
	}

	void CameraController::MoveAlongWorldAxisY(float offset)
	{
		auto& v = m_camera->GetPosition();
		v[1] += offset;
	}

	void CameraController::MoveAlongWorldAxisZ(float offset)
	{
		auto& v = m_camera->GetPosition();
		v[0] += offset;
	}
}