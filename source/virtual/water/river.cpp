#include "river.h"

namespace Virtual
{
    River::River()
        : m_geom(nullptr)
    {
    }

    River::~River()
    {
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
}
