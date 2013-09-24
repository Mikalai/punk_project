#include "../system/buffer.h"
#include "oct_tree.h"
#include "aabb.h"
#include "line3d.h"
#include "triangle3d.h"

#include <istream>
#include <ostream>
#include <algorithm>

namespace Math
{
    OctTree::OctTree(OctTree* p)
        : m_parent(p)
        , m_bbox()
        , m_face_count(0)
        , m_is_finale(false)
        , m_cur_depth(p ? p->m_cur_depth+1 : 0)
    {}

    OctTree::OctTree(const OctTree& t)
        : m_parent(m_parent)
        , m_bbox(m_bbox)
        , m_face_count(m_face_count)
        , m_face_list(m_face_list)
        , m_is_finale(m_is_finale)
        , m_cur_depth(t.m_cur_depth)
        , m_right_front_up(t.m_right_front_up.get() ? new OctTree(*t.m_right_back_up) : 0)
        , m_right_front_down(t.m_right_front_down.get() ? new OctTree(*t.m_right_front_down) : 0)
        , m_right_back_up(t.m_right_back_up.get() ? new OctTree(*t.m_right_back_up) : 0)
        , m_right_back_down(t.m_right_back_down.get() ? new OctTree(*t.m_right_back_down) : 0)
        , m_left_front_up(t.m_left_front_up.get() ? new OctTree(*t.m_left_front_up) : 0)
        , m_left_front_down(t.m_left_front_down.get() ? new OctTree(*t.m_left_front_down) : 0)
        , m_left_back_up(t.m_left_back_up.get() ? new OctTree(*t.m_left_back_up) : 0)
        , m_left_back_down(t.m_left_back_down.get() ? new OctTree(*t.m_left_back_down) : 0)
    {}

    void OctTree::SetData(const OctTree::FaceList& fl, const OctTree::VertexList& vl)
    {
        //m_face_list = fl;
        m_cur_depth = 0;
        //triaglesCount = fl.Face.Count;
        //vertexList = vl;
        m_bbox.Create((const float*)&vl[0], sizeof(vec3), vl.size());
        Build(fl, vl);
    }

    OctTree* OctTree::Build(const FaceList& fl, const VertexList& vertexList)
    {
        m_cur_depth = m_parent != 0 ? m_parent->m_cur_depth + 1 : 0;
        if (m_cur_depth >= MaxDepth)
        {
            for (auto i = fl.begin(); i != fl.end(); ++i)
            {
                m_face_list.push_back(*i);
                m_face_count++;
            }
            m_is_finale = true;
            return this;
        }

        FaceList temp_face_list;
        temp_face_list.reserve(fl.size());
        FaceList::const_iterator end = fl.end();
        for (FaceList::const_iterator i = fl.begin(); i != end; ++i)
        {
            const ivec3& face = *i;
            const vec3& p1 = vertexList[face.X()];
            const vec3& p2 = vertexList[face.Y()];
            const vec3& p3 = vertexList[face.Z()];

            if (CrossTriangleAxisAlignedBox(Triangle3D(p1, p2, p3), m_bbox) == Relation::INTERSECT)
            {
                temp_face_list.push_back(face);
                ++m_face_count;
            }
        }

        if ((m_parent == 0 || m_face_count > MaxFaceCount) && (m_face_count != m_parent->m_face_count))
        {
            const vec3& Min = m_bbox.MinPoint();
            const vec3& Max = m_bbox.MaxPoint();
            const vec3 mid = (Min + Max) / 2.0f;
            m_right_front_up.reset(new OctTree(this));
            m_right_front_up->m_bbox.MinPoint() = vec3(mid.X(), mid.Y(), mid.Z());
            m_right_front_up->m_bbox.MaxPoint() = vec3(Max.X(), Max.Y(), Max.Z());
            m_right_front_up->Build(temp_face_list, vertexList);

            m_right_front_down.reset(new OctTree(this));
            m_right_front_down->m_bbox.MinPoint() = vec3(mid.X(), mid.Y(), Min.Z());
            m_right_front_down->m_bbox.MaxPoint() = vec3(Max.X(), Max.Y(), mid.Z());
            m_right_front_down->Build(temp_face_list, vertexList);

            m_left_front_up.reset(new OctTree(this));
            m_left_front_up->m_bbox.MinPoint() = vec3(Min.X(), mid.Y(), mid.Z());
            m_left_front_up->m_bbox.MaxPoint() = vec3(mid.X(), Max.Y(), Max.Z());
            m_left_front_up->Build(temp_face_list,vertexList);

            m_left_front_down.reset(new OctTree(this));
            m_left_front_down->m_bbox.MinPoint() = vec3(Min.X(), mid.Y(), Min.Z());
            m_left_front_down->m_bbox.MaxPoint() = vec3(mid.X(), Max.Y(), mid.Z());
            m_left_front_down->Build(temp_face_list,vertexList);
            ///////////////////////////////////////////////

            m_right_back_up.reset(new OctTree(this));
            m_right_back_up->m_bbox.MinPoint() = vec3(mid.X(), Min.Y(), mid.Z());
            m_right_back_up->m_bbox.MaxPoint() = vec3(Max.X(), mid.Y(), Max.Z());
            m_right_back_up->Build(temp_face_list,vertexList);

            m_right_back_down.reset(new OctTree(this));
            m_right_back_down->m_bbox.MinPoint() = vec3(mid.X(), Min.Y(), Min.Z());
            m_right_back_down->m_bbox.MaxPoint() = vec3(Max.X(), mid.Y(), mid.Z());
            m_right_back_down->Build(temp_face_list,vertexList);

            m_left_back_up.reset(new OctTree(this));
            m_left_back_up->m_bbox.MinPoint() = vec3(Min.X(), Min.Y(), mid.Z());
            m_left_back_up->m_bbox.MaxPoint() = vec3(mid.X(), mid.Y(), Max.Z());
            m_left_back_up->Build(temp_face_list,vertexList);

            m_left_back_down.reset(new OctTree(this));
            m_left_back_down->m_bbox.MinPoint() = vec3(Min.X(), Min.Y(), Min.Z());
            m_left_back_down->m_bbox.MaxPoint() = vec3(mid.X(), mid.Y(), mid.Z());
            m_left_back_down->Build(temp_face_list, vertexList);
        }
        else
        {
            m_face_list = temp_face_list;
            m_is_finale = true;
        }
        return this;
    }

    OctTree::FaceList OctTree::Cross(const Line3D& line)
    {
        return CrossAll(line);
    }

    OctTree::FaceList OctTree::CrossAll(const Line3D& line) const
    {
        FaceList fl;
        float tmin;
        vec3 v;
        if (CrossLineAxisAlignedBox(line, m_bbox, tmin, v) == Relation::INTERSECT)
        {
            if (m_is_finale)
                fl.insert(fl.end(), m_face_list.begin(), m_face_list.end());
            else
            {
                FaceList res;
                res = m_right_front_up->CrossAll(line);
                if (!res.empty())
                    fl.insert(fl.end(), res.begin(), res.end());
                res = m_right_front_down->CrossAll(line);
                if (!res.empty())
                    fl.insert(fl.end(), res.begin(), res.end());
                res = m_left_front_up->CrossAll(line);
                if (!res.empty())
                    fl.insert(fl.end(), res.begin(), res.end());
                res = m_left_front_down->CrossAll(line);
                if (!res.empty())
                    fl.insert(fl.end(), res.begin(), res.end());
                res = m_right_back_up->CrossAll(line);
                if (!res.empty())
                    fl.insert(fl.end(), res.begin(), res.end());
                res = m_right_back_down->CrossAll(line);
                if (!res.empty())
                    fl.insert(fl.end(), res.begin(), res.end());
                res = m_left_back_up->CrossAll(line);
                if (!res.empty())
                    fl.insert(fl.end(), res.begin(), res.end());
                res = m_left_back_down->CrossAll(line);
                if (!res.empty())
                    fl.insert(fl.end(), res.begin(), res.end());
            }
            return fl;
        }
        return FaceList();
    }

    void SaveOctTree(System::Buffer* buffer, const OctTree& value)
    {
        buffer->WriteSigned32(value.m_cur_depth);
        SaveBoundingBox(buffer, value.m_bbox);
        buffer->WriteSigned32(value.m_is_finale);
        buffer->WriteSigned32(value.m_face_count);
        int has_data = (int)value.m_face_list.size();
        buffer->WriteSigned32(has_data);
        if (value.m_face_count && has_data)
            for (auto& p : value.m_face_list)
                SaveVector3i(buffer, p);

        if (value.m_is_finale)
            return;

        int flag = value.m_right_front_up.get() != 0;
        buffer->WriteSigned32(flag);
        if (flag)
            SaveOctTree(buffer, *value.m_right_front_up);

        flag = value.m_right_front_down.get() != 0;
        buffer->WriteSigned32(flag);
        if (flag)
            SaveOctTree(buffer, *value.m_right_front_down);

        flag = value.m_right_back_up.get() != 0;
        buffer->WriteSigned32(flag);
        if (flag)
            SaveOctTree(buffer, *value.m_right_back_up);

        flag = value.m_right_back_down.get() != 0;
        buffer->WriteSigned32(flag);
        if (flag)
            SaveOctTree(buffer, *value.m_right_back_down);

        flag = value.m_left_front_up.get() != 0;
        buffer->WriteSigned32(flag);
        if (flag)
            SaveOctTree(buffer, *value.m_left_front_up);

        flag = value.m_left_front_down.get() != 0;
        buffer->WriteSigned32(flag);
        if (flag)
            SaveOctTree(buffer, *value.m_left_front_down);

        flag = value.m_left_back_up.get() != 0;
        buffer->WriteSigned32(flag);
        if (flag)
            SaveOctTree(buffer, *value.m_left_back_up);

        flag = value.m_left_back_down.get() != 0;
        buffer->WriteSigned32(flag);
        if (flag)
            SaveOctTree(buffer, *value.m_left_back_down);
    }

    void LoadOctTree(System::Buffer* buffer, OctTree& value)
    {
        value.m_cur_depth = buffer->ReadSigned32();
        LoadBoundingBox(buffer, value.m_bbox);
        value.m_is_finale = buffer->ReadSigned32();
        value.m_face_count = buffer->ReadSigned32();
        int has_data = buffer->ReadSigned32();
        if (value.m_face_count && has_data)
        {
            value.m_face_list.resize(value.m_face_count);
            for (auto& p : value.m_face_list)
                LoadVector3i(buffer, p);
        }

        if (value.m_is_finale)
            return;

        int flag = buffer->ReadSigned32();
        if (flag)
        {
            value.m_right_front_up.reset(new OctTree);
            value.m_right_front_up->m_parent = &value;
            LoadOctTree(buffer, *value.m_right_front_up);
        }

        flag = buffer->ReadSigned32();
        if (flag)
        {
            value.m_right_front_down.reset(new OctTree);
            value.m_right_front_down->m_parent = &value;
            LoadOctTree(buffer, *value.m_right_front_down);
        }

        flag = buffer->ReadSigned32();
        if (flag)
        {
            value.m_right_back_up.reset(new OctTree);
            value.m_right_back_up->m_parent = &value;
            LoadOctTree(buffer, *value.m_right_back_up);
        }

        flag = buffer->ReadSigned32();
        if (flag)
        {
            value.m_right_back_down.reset(new OctTree);
            value.m_right_back_down->m_parent = &value;
            LoadOctTree(buffer, *value.m_right_back_down);
        }

        flag = buffer->ReadSigned32();
        if (flag)
        {
            value.m_left_front_up.reset(new OctTree);
            value.m_left_front_up->m_parent = &value;
            LoadOctTree(buffer, *value.m_left_front_up);
        }

        flag = buffer->ReadSigned32();
        if (flag)
        {
            value.m_left_front_down.reset(new OctTree);
            value.m_left_front_down->m_parent = &value;
            LoadOctTree(buffer, *value.m_left_front_down);
        }

        flag = buffer->ReadSigned32();
        if (flag)
        {
            value.m_left_back_up.reset(new OctTree);
            value.m_left_back_up->m_parent = &value;
            LoadOctTree(buffer, *value.m_left_back_up);
        }

        flag = buffer->ReadSigned32();
        if (flag)
        {
            value.m_left_back_down.reset(new OctTree);
            value.m_left_back_down->m_parent = &value;
            LoadOctTree(buffer, *value.m_left_back_down);
        }
    }
}
