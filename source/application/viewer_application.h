#ifndef VIEWER_APPLICATION_H
#define VIEWER_APPLICATION_H

#include "application.h"

namespace Punk
{
    class ViewerApplication : public Application
    {
    public:
        ViewerApplication();

        void UpdateCameraDirection(System::Event* event);
        void UpdateCameraDistance(System::Event* event);
        void MoveCameraForward(System::Event* event);
        void MoveCameraBackward(System::Event* event);
        void MoveCameraLeft(System::Event* event);
        void MoveCameraRight(System::Event* event);
        void IncreaseDistance(System::Event* event);
        void DecreaseDistance(System::Event* event);

        const Math::mat4 GetViewMatrix() const;
    private:
        Math::SphericalCoordinate m_camera_direction;
        Math::vec3 m_camera_view;
        float m_distance;
    };
}

#endif // VIEWER_APPLICATION_H
