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
        if (!m_bbox.Create(m_points))
			return (out_error() << "Can't create bounding box for convex shape" << std::endl, false);

        if (!m_bsphere.Create(m_points))
			return (out_error() << "Can't create bounding sphere for convex shape" << std::endl, false);

		return true;
	}

    void ConvexShapeMesh::Save(System::Buffer *buffer) const
	{
		if (m_points.empty() || m_faces.empty() || m_normals.empty())
            throw System::PunkException("Unable to save convex shape");

		int size = (int)m_points.size();		
        buffer->WriteSigned32(size);
        for (auto& p : m_points)
            p.Save(buffer);

        size = (int)m_faces.size();
        buffer->WriteSigned32(size);
        for (auto& p : m_faces)
            p.Save(buffer);

		size = (int)m_normals.size();
        buffer->WriteSigned32(size);
        for (auto& p : m_normals)
            p.Save(buffer);
	}

    void ConvexShapeMesh::Load(System::Buffer *buffer)
	{
        int size = buffer->ReadSigned32();
		m_points.resize(size);
        for (auto& p : m_points)
            p.Load(buffer);

        size = buffer->ReadSigned32();
		m_faces.resize(size);
        for (auto& p : m_faces)
            p.Load(buffer);

        size = buffer->ReadSigned32();
		m_normals.resize(size);
        for (auto& p : m_normals)
            p.Load(buffer);
	}
}
