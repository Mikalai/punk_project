#include "camera.h"
#include "../system/system.h"
#include "../math/math.h"

namespace Utility
{
	Camera::Camera() : Math::Frustum(), m_mouse_sense(0.001f), m_phi(0), m_psy(0),
		m_move_forward(System::PUNK_KEY_W),
		m_move_backward(System::PUNK_KEY_S),
		m_move_left(System::PUNK_KEY_A),
		m_move_right(System::PUNK_KEY_D)
	{
		System::Mouse::GetInstance()->LockInWindow(false);
		//System::Mouse::GetInstance()->Show(false);

		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(this, &Camera::OnMouseMove));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(this, &Camera::OnIdle));

		System::ConfigFile conf;
		conf.Open(System::Window::GetInstance()->GetTitle());
		if (conf.IsExistOption(L"mouse_sense"))
		{
			m_mouse_sense = conf.ReadOptionInt(L"mouse_sense") / 10000.0f;
		}
		else
		{
			conf.WriteOptionInt(L"mouse_sense", int(10000.0f*m_mouse_sense));
		}

		if (conf.IsExistOption(L"move_forward"))
		{
			m_move_forward = conf.ReadOptionInt(L"move_forward");
		}
		else
		{
			conf.WriteOptionInt(L"move_forward", m_move_forward);
		}

		if (conf.IsExistOption(L"move_backward"))
		{
			m_move_backward = conf.ReadOptionInt(L"move_backward");
		}
		else
		{
			conf.WriteOptionInt(L"move_backward", m_move_backward);
		}

		if (conf.IsExistOption(L"move_left"))
		{
			m_move_left = conf.ReadOptionInt(L"move_left");
		}
		else
		{
			conf.WriteOptionInt(L"move_left", m_move_left);
		}

		if (conf.IsExistOption(L"move_right"))
		{
			m_move_right = conf.ReadOptionInt(L"move_right");
		}
		else
		{
			conf.WriteOptionInt(L"move_right", m_move_right);
		}


			
		conf.Close();
	}

	void Camera::OnMouseMove(System::Event* e)
	{
		if (!System::Mouse::GetInstance()->IsLocked())
			return;

		System::MouseMoveEvent* event = dynamic_cast<System::MouseMoveEvent*>(e);
		if (!e)
			throw System::SystemError(L"Unexpected event");
		
		m_phi -= float(event->x - event->x_prev)*m_mouse_sense;
		m_psy -= float(event->y - event->y_prev)*m_mouse_sense;

		if (m_phi < 0)
			m_phi = 2*Math::PI;
		if (m_phi > 2*Math::PI)
			m_phi = 0;
		if (m_psy < -Math::PI/2+Math::EPS)
			m_psy = -Math::PI/2+Math::EPS;
		if (m_psy > Math::PI/2-Math::EPS)
			m_psy = Math::PI/2-Math::EPS;


		Math::mat4 y_axis = Math::mat4::CreateYRotation(m_phi);
		Math::mat4 x_axis = Math::mat4::CreateXRotation(m_psy);

		m_direction = (y_axis*x_axis*Math::vec4(0, 0, 1, 1)).XYZ().Normalized();

		UpdateMatrix();
	}

	void Camera::OnIdle(System::Event* e)
	{
		float dt = 10*m_timer.GetElapsedTime();
		if (System::Keyboard::GetInstance()->GetKeyState(m_move_forward))
			m_position += m_direction.Normalized()*dt;
		if (System::Keyboard::GetInstance()->GetKeyState(m_move_backward))
			m_position -= m_direction.Normalized()*dt;
		if (System::Keyboard::GetInstance()->GetKeyState(m_move_left))
			m_position += Math::vec3(0,1,0).Cross(m_direction).Normalized()*dt;
		if (System::Keyboard::GetInstance()->GetKeyState(m_move_right))
			m_position -= Math::vec3(0,1,0).Cross(m_direction).Normalized()*dt;
		UpdateMatrix();
		m_timer.UpdateStartPoint();
	}

	Camera::~Camera()
	{
		//System::Mouse::GetInstance()->LockInWindow(false);
		//System::Mouse::GetInstance()->Show(false);
		System::EventManager::GetInstance()->UnsubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(this, &Camera::OnMouseMove));
		System::EventManager::GetInstance()->UnsubscribeHandler(System::EVENT_IDLE, System::EventHandler(this, &Camera::OnIdle));
	}
}