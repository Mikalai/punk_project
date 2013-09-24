#include "../system/logger.h"
#include "../system/errors/module.h"
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

    void SaveBoundingBox(System::Buffer* buffer, const ConvexShapeMesh& value)
    {
        if (value.m_points.empty() || value.m_faces.empty() || value.m_normals.empty())
            throw System::PunkException("Unable to save convex shape");

        int size = (int)value.m_points.size();
        buffer->WriteSigned32(size);
        for (auto& p : value.m_points)
            SaveVector3f(buffer, p);

        size = (int)value.m_faces.size();
        buffer->WriteSigned32(size);
        for (auto& p : value.m_faces)
            SaveVector3i(buffer, p);

        size = (int)value.m_normals.size();
        buffer->WriteSigned32(size);
        for (auto& p : value.m_normals)
            SaveVector3f(buffer, p);
    }

    void LoadBoundingBox(System::Buffer* buffer, ConvexShapeMesh& value)
    {
        int size = buffer->ReadSigned32();
        value.m_points.resize(size);
        for (auto& p : value.m_points)
            LoadVector3f(buffer, p);

        size = buffer->ReadSigned32();
        value.m_faces.resize(size);
        for (auto& p : value.m_faces)
            SaveVector3i(buffer, p);

        size = buffer->ReadSigned32();
        value.m_normals.resize(size);
        for (auto& p : value.m_normals)
            LoadVector3f(buffer, p);

    }
}
