#include "river.h"
#include "../../utility/module.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(River, "Virtual.River", PUNK_RIVER, &System::Object::Info.Type);

    River::River()
        : m_geom(nullptr)
        , m_task(nullptr)
    {
        Info.Add(this);
    }

    River::~River()
    {
        Info.Remove(this);
    }

    void River::SetGeometry(StaticGeometry* value)
    {
        m_geom = value;
    }

    const StaticGeometry* River::GetGeometry() const
    {
        return m_geom;
    }

    StaticGeometry* River::GetGeometry()
    {
        return m_geom;
    }

    void River::SetFlowSpeed(float value)
    {
        m_flow_speed = value;
    }

    float River::GetFlowSpeed() const
    {
        return m_flow_speed;
    }

    void River::SetFlowDirection(const Math::vec3& value)
    {
        m_flow_direction = value;
    }

    const Math::vec3& River::GetFlowDirection() const
    {
        return m_flow_direction;
    }

    void River::SetStaticMeshFilename(const System::string& value)
    {
        m_filename = value;
    }

    const System::string River::GetStaticMeshFilename() const
    {
        return m_filename;
    }

    void River::SetStreamPosition(const Math::vec3& value)
    {
        m_position = value;
    }

    const Math::vec3& River::GetStreamPosition() const
    {
        return m_position;
    }

    Utility::AsyncParserTask* River::Task() const
    {
        return m_task;
    }

    Utility::AsyncParserTask* River::Task(Utility::AsyncParserTask* value)
    {
        if (m_task)
            delete m_task;
        return m_task = value;
    }

    void River::SetName(const System::string& name)
    {
        m_name = name;
    }

    const System::string& River::GetName() const
    {
        return m_name;
    }

}
