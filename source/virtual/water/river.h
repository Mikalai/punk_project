#ifndef PUNK_VIRTUAL_RIVER_H
#define PUNK_VIRTUAL_RIVER_H

#include "../data/static_geometry.h"

namespace Virtual
{
    class River : public System::Object, public System::Aspect<River*, System::string>
    {
    public:
        River();
        virtual ~River();

        void SetGeometry(StaticGeometry* value);
        const StaticGeometry* GetGeometry() const;
        StaticGeometry* GetGeometry();

        void SetFlowSpeed(float value);
        float GetFlowSpeed() const;

        void SetFlowDirection(const Math::vec3& value);
        const Math::vec3& GetFlowDirection() const;

        void SetStaticMeshFilename(const System::string& value);
        const System::string GetStaticMeshFilename() const;

        void SetStreamPosition(const Math::vec3& value);
        const Math::vec3& GetStreamPosition() const;

    private:
        Math::vec3 m_position;
        System::string m_filename;
        float m_flow_speed;
        Math::vec3 m_flow_direction;
        StaticGeometry* m_geom;
    };
}

#endif // PUNK_VIRTUAL_RIVER_H
