#include "../system/errors/module.h"
#include "../system/logger.h"
#include "portal.h"

namespace Math
{
	bool Portal::SetPoints(const Portal::PointsCollection& points)
	{
		if (points.size() < 3)
			return (out_error() << "Can't create portal with " << points.size() << " points" << std::endl, false);

		m_points = points;

		const vec3& p0 = m_points[0];
		const vec3& p1 = m_points[1];
		const vec3& p2 = m_points[2];

		m_plane.Set(p0, p1, p2);

		return true;
	}    

	const Portal operator * (const mat4& m, const Portal& p)
	{
		Portal::PointsCollection points;
		for (auto& point : p)
		{
			points.push_back(m*point);
		}
		Portal result;
		result.SetPoints(points);
		return result;
	}

    void SaveBoundingBox(System::Buffer *buffer, const Portal& value)
    {
        if (value.m_points.empty())
            throw System::PunkException("Can't save bad portal");

        int size = (int)value.m_points.size();
        buffer->WriteSigned32(size);
        for (auto& p : value.m_points)
            SaveVector3f(buffer, p);
        SavePlane(buffer, value.m_plane);
    }

    void LoadBoundingBox(System::Buffer *buffer, Portal& value)
    {
        int size = buffer->ReadSigned32();
        value.m_points.resize(size);
        for (auto& p : value.m_points)
            LoadVector3f(buffer, p);
        LoadPlane(buffer, value.m_plane);
    }
}
