#ifndef PUNK_VIRTUAL_RIVER_H
#define PUNK_VIRTUAL_RIVER_H

#include "../data/static_geometry.h"

namespace Utility
{
    class AsyncParserTask;
}

namespace Virtual
{
    class River : public System::Object
    {
    public:
        River();
        River(const River&) = delete;
        River& operator = (const River&) = delete;
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

        Utility::AsyncParserTask* Task() const;
        Utility::AsyncParserTask* Task(Utility::AsyncParserTask* value);

        void SetName(const System::string& name);
        const System::string& GetName() const;

    private:
        Math::vec3 m_position;
        System::string m_filename;
        float m_flow_speed;
        Math::vec3 m_flow_direction;
        StaticGeometry* m_geom;
        Utility::AsyncParserTask* m_task;
        System::string m_name;
        PUNK_OBJECT(River)
    };
}

#endif // PUNK_VIRTUAL_RIVER_H
