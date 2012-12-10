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

	bool Portal::Save(std::ostream& stream) const
	{
		if (m_points.empty())
			return (out_error() << "Can't save portal points, because there is no points" << std::endl, false);

		int size = (int)m_points.size();
		stream.write((char*)&size, sizeof(size));
		stream.write((char*)&m_points[0], sizeof(m_points[0]));
		m_plane.Save(stream);
		return true;
	}

	bool Portal::Load(std::istream& stream)
	{
		int size = 0;
		stream.read((char*)&size, sizeof(size));
		m_points.resize(size);
		stream.read((char*)&m_points[0], sizeof(m_points[0]));
		m_plane.Load(stream);
		return true;
	}

	const Portal operator * (const mat4& m, const Portal& p)
	{
		Portal::PointsCollection points;
		for each (auto& point in p)
		{
			points.push_back(m*point);
		}
		Portal result;
		result.SetPoints(points);
		return result;
	}
}