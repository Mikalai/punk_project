#include "../system/logger.h"
#include "convex_shape_mesh.h"

namespace Math
{
	void ConvexShapeMesh::SetPoints(const ConvexShapeMesh::PointsCollection& value)
	{
		m_points = value;
		UpdateBoundingVolumes();
	}

	bool ConvexShapeMesh::UpdateBoundingVolumes()
	{
		if (!m_bbox.Create((float*)&m_points[0], (int)m_points.size(), sizeof(m_points[0])))
			return (out_error() << "Can't create bounding box for convex shape" << std::endl, false);

		if (!m_bsphere.Create((float*)&m_points[0], (int)m_points.size(), sizeof(m_points[0])))
			return (out_error() << "Can't create bounding sphere for convex shape" << std::endl, false);

		return true;
	}

	bool ConvexShapeMesh::Save(std::ostream& stream) const
	{
		if (m_points.empty() || m_faces.empty() || m_normals.empty())
			return false;

		int size = (int)m_points.size();		
		stream.write((char*)&size, sizeof(size));
		stream.write((char*)&m_points[0], sizeof(m_points[0])*size);
		size = (int)m_faces.size();
		stream.write((char*)&size, sizeof(size));
		stream.write((char*)&m_faces[0], sizeof(m_faces[0])*size);
		size = (int)m_normals.size();
		stream.write((char*)&size, sizeof(size));
		stream.write((char*)&m_normals[0], sizeof(m_normals[0])*size);
		return true;
	}

	bool ConvexShapeMesh::Load(std::istream& stream)
	{
		int size = 0;
		stream.read((char*)&size, sizeof(size));
		m_points.resize(size);
		stream.read((char*)&m_points[0], sizeof(m_points[0])*size);
		size = 0;		
		stream.read((char*)&size, sizeof(size));
		m_faces.resize(size);
		stream.read((char*)&m_faces[0], sizeof(m_faces[0])*size);
		size = 0;
		stream.read((char*)&size, sizeof(size));
		m_normals.resize(size);
		stream.read((char*)&m_normals[0], sizeof(m_normals[0])*size);
		return true;
	}
}
