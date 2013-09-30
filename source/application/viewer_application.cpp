#include "viewer_application.h"

namespace Punk
{
    ViewerApplication::ViewerApplication()
        : m_distance(5)
        , m_speed(1)
    {
        GetKeyMap()->Add(System::EVENT_MOUSE_MOVE, System::Mouse::LEFT_BUTTON, System::EventHandler(this, &ViewerApplication::UpdateCameraDirection));
        GetKeyMap()->Add(System::EVENT_KEYBOARD_HOLD_BUTTON, System::PUNK_KEY_W, System::EventHandler(this, &ViewerApplication::MoveCameraForward));
        GetKeyMap()->Add(System::EVENT_KEYBOARD_HOLD_BUTTON, System::PUNK_KEY_S, System::EventHandler(this, &ViewerApplication::MoveCameraBackward));
        GetKeyMap()->Add(System::EVENT_KEYBOARD_HOLD_BUTTON, System::PUNK_KEY_A, System::EventHandler(this, &ViewerApplication::MoveCameraLeft));
        GetKeyMap()->Add(System::EVENT_KEYBOARD_HOLD_BUTTON, System::PUNK_KEY_D, System::EventHandler(this, &ViewerApplication::MoveCameraRight));
        GetKeyMap()->Add(System::EVENT_MOUSE_WHEEL, 1, System::EventHandler(this, &ViewerApplication::IncreaseDistance));
        GetKeyMap()->Add(System::EVENT_MOUSE_WHEEL, -1, System::EventHandler(this, &ViewerApplication::DecreaseDistance));
    }

    void ViewerApplication::UpdateCameraDirection(System::Event* e)
    {
        auto* event = (System::MouseMoveEvent*)e;
        float phi = m_camera_direction.Phi();
        float psy = m_camera_direction.Theta();
        phi += Math::Recount::DegToRad(event->x - event->x_prev);
        psy += Math::Recount::DegToRad(event->y - event->y_prev);

        if (phi < -M_PI)
            phi = M_PI;
        else if (phi > M_PI)
            phi = -M_PI;

        if (psy > M_PI/2.0f - 1.0f/180.0f)
            psy = M_PI/2.0f - 1.0f/180.0f;
        if (psy < -(M_PI/2.0f - 1.0f/180.0f))
            psy = -(M_PI/2.0f - 1.0f/180.0f);

        m_camera_direction.Phi(phi);
        m_camera_direction.Theta(psy);
    }

    void ViewerApplication::UpdateCameraDistance(System::Event* event)
    {
        auto e = (System::MouseWheelEvent*)event;
        float r = m_camera_direction.R();
        r += e->delta * 0.1f;
        m_camera_direction.R(r);
    }

    void ViewerApplication::MoveCameraForward(System::Event* event)
    {
        auto dir = Math::Recount::SphericalToCartesian(m_camera_direction).Negated();
        auto e = (System::IdleEvent*)event;
        m_camera_view += dir * e->elapsed_time_s * m_speed;
    }

    void ViewerApplication::MoveCameraBackward(System::Event* event)
    {
        auto dir = Math::Recount::SphericalToCartesian(m_camera_direction);
        auto e = (System::IdleEvent*)event;
        m_camera_view += dir * e->elapsed_time_s * m_speed;
    }

    void ViewerApplication::MoveCameraLeft(System::Event* event)
    {
        auto dir = Math::Recount::SphericalToCartesian(m_camera_direction);
        auto left = Math::vec3(0,0,1).Cross(dir);
        auto e = (System::IdleEvent*)event;
        m_camera_view += left * e->elapsed_time_s * m_speed;
    }

    void ViewerApplication::MoveCameraRight(System::Event* event)
    {        auto dir = Math::Recount::SphericalToCartesian(m_camera_direction).Negated();
             auto left = Math::vec3(0,0,1).Cross(dir);
             auto e = (System::IdleEvent*)event;
             m_camera_view += left * e->elapsed_time_s * m_speed;

    }

    void ViewerApplication::DecreaseDistance(System::Event *event)
    {
        m_distance -= 0.1f;
        m_distance = std::max(m_distance, 0.1f);
    }

    void ViewerApplication::IncreaseDistance(System::Event* event)
    {
        m_distance += 0.1f;
        m_distance = std::min(m_distance, 10.0f);
    }

    const Math::mat4 ViewerApplication::GetViewMatrix() const
    {
        auto dir = Math::Recount::SphericalToCartesian(m_camera_direction).Negated();
        auto pos = m_camera_view + dir * m_distance;
        return Math::mat4::CreateTargetCameraMatrix(pos, m_camera_view, Math::vec3(0, 0, 1));
    }

    const Math::mat4 ViewerApplication::GetProjectionMatrix() const
    {
        return Math::mat4::CreatePerspectiveProjection(Math::PI / 4, GetWindow()->GetWidth(), GetWindow()->GetHeight(), 1, 100);
    }

    void ViewerApplication::SetCameraSpeed(float value)
    {
        m_speed = value;
    }
}
