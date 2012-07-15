#include <iostream>
#include "camera.h"
#include "../system/system.h"
#include "../math/math.h"

namespace Utility
{
	Camera::Camera() : Math::Frustum(), m_mouse_sense(0.001f), m_phi(0), m_psy(0),
		m_move_forward(System::PUNK_KEY_W),
		m_move_backward(System::PUNK_KEY_S),
		m_move_left(System::PUNK_KEY_A),
		m_move_right(System::PUNK_KEY_D),
		m_camera_type(CAMERA_TYPE_FPS),
		m_height_offset(20),
		m_base_height(0)
	{
		System::Mouse::Instance()->LockInWindow(false);
		//System::Mouse::Instance()->Show(false);

	/*	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(this, &Camera::OnMouseMove));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(this, &Camera::OnIdle));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Camera::OnKeyDown));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_WHEEL, System::EventHandler(this, &Camera::OnMouseScroll));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &Camera::OnResize));*/

		System::ConfigFile conf;
		conf.Open(System::Window::Instance()->GetTitle());
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
		if (m_camera_type == CAMERA_TYPE_FPS)
		{
			if (!System::Mouse::Instance()->IsLocked())
				return;

			System::MouseMoveEvent* event = static_cast<System::MouseMoveEvent*>(e);

			m_phi -= float(event->x - event->x_prev)*m_mouse_sense;
			m_psy += float(event->y - event->y_prev)*m_mouse_sense;

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

			m_direction = ((y_axis*x_axis)*Math::vec4(0, 0, 1, 0)).XYZ().Normalized();

			UpdateMatrix();
		}
		else if (m_camera_type == CAMERA_TYPE_RTS)
		{
		}
	}

	void Camera::OnIdle(System::Event* e)
	{
		if (m_camera_type == CAMERA_TYPE_FPS)
		{
			float dt = m_timer.GetElapsedTime();
			if (System::Keyboard::Instance()->GetKeyState(m_move_forward))
				m_position -= m_direction.Normalized()*dt;
			if (System::Keyboard::Instance()->GetKeyState(m_move_backward))
				m_position += m_direction.Normalized()*dt;
			if (System::Keyboard::Instance()->GetKeyState(m_move_left))
				m_position -= Math::vec3(0,1,0).Cross(m_direction).Normalized()*dt;
			if (System::Keyboard::Instance()->GetKeyState(m_move_right))
				m_position += Math::vec3(0,1,0).Cross(m_direction).Normalized()*dt;
			m_position[1] = m_base_height;
		}
		else if (m_camera_type == CAMERA_TYPE_RTS)
		{
			float dt = m_height_offset*m_timer.GetElapsedTime();
			if (System::Keyboard::Instance()->GetKeyState(m_move_forward))
				m_position -= Math::vec3(0, 0, 1)*dt;
			if (System::Keyboard::Instance()->GetKeyState(m_move_backward))
				m_position += Math::vec3(0, 0, 1)*dt;
			if (System::Keyboard::Instance()->GetKeyState(m_move_left))
				m_position -= Math::vec3(1,0,0)*dt;
			if (System::Keyboard::Instance()->GetKeyState(m_move_right))
				m_position += Math::vec3(1,0,0)*dt;	
			m_position[1] = m_base_height + m_height_offset;	
		}	
		UpdateMatrix();			
		m_timer.UpdateStartPoint();
	}

	void Camera::OnKeyDown(System::Event* e)
	{
		System::KeyDownEvent* event = static_cast<System::KeyDownEvent*>(e);
		switch(event->key)
		{
		case System::PUNK_KEY_F1:
			m_camera_type = CAMERA_TYPE_FPS;
			m_direction = Math::vec3(0, 0, 1);
			break;
		case System::PUNK_KEY_F2:
			m_camera_type = CAMERA_TYPE_RTS;
			m_direction = Math::vec3(0, 1, 1).Normalized();
			break;	
		case System::PUNK_KEY_SHIFT:
			{
				System::Mouse::Instance()->Show(System::Mouse::Instance()->IsLocked());
				System::Mouse::Instance()->LockInWindow(!System::Mouse::Instance()->IsLocked());				
			}
			break;
		}
	}

	void Camera::OnMouseScroll(System::Event* e)
	{
		System::MouseWheelEvent* event = static_cast<System::MouseWheelEvent*>(e);
		m_height_offset += event->delta;
		if (m_height_offset < 0)
			m_height_offset = 0;
	}

	void Camera::OnResize(System::Event* e)
	{
		System::WindowResizeEvent* event = static_cast<System::WindowResizeEvent*>(e);
		m_aspect = System::Window::Instance()->GetWidth() / (double)System::Window::Instance()->GetHeight();
		UpdateMatrix();
	}

	Camera::~Camera()
	{
		//System::Mouse::Instance()->LockInWindow(false);
		//System::Mouse::Instance()->Show(false);
		System::EventManager::Instance()->UnsubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(this, &Camera::OnMouseMove));
		System::EventManager::Instance()->UnsubscribeHandler(System::EVENT_IDLE, System::EventHandler(this, &Camera::OnIdle));
		System::EventManager::Instance()->UnsubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Camera::OnKeyDown));
		System::EventManager::Instance()->UnsubscribeHandler(System::EVENT_MOUSE_WHEEL, System::EventHandler(this, &Camera::OnKeyDown));
		System::EventManager::Instance()->UnsubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &Camera::OnResize));
	}
}