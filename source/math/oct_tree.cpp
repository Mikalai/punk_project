#include "oct_tree.h"
#include "aabb.h"
#include "line3d.h"

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

        if (m_bbox.DoCrossTriangle(p1, p2, p3))
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
    if (m_bbox.DoCrossLine(line))
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

bool OctTree::Save(std::ostream& stream) const
{
    stream.write((char*)&m_cur_depth, sizeof(m_cur_depth));
    m_bbox.Save(stream);
    stream.write((char*)&m_is_finale, sizeof(m_is_finale));
    stream.write((char*)&m_face_count, sizeof(m_face_count));
    int has_data = (int)m_face_list.size();
    stream.write((char*)&has_data, sizeof(has_data));
    if (m_face_count && has_data)
        stream.write((char*)&m_face_list[0], sizeof(ivec3)*m_face_count);

    if (m_is_finale)
        return true;

    int flag = m_right_front_up.get() != 0;
    stream.write((char*)&flag, sizeof(flag));
    if (flag)
        m_right_front_up->Save(stream);

    flag = m_right_front_down.get() != 0;
    stream.write((char*)&flag, sizeof(flag));
    if (flag)
        m_right_front_down->Save(stream);

    flag = m_right_back_up.get() != 0;
    stream.write((char*)&flag, sizeof(flag));
    if (flag)
        m_right_back_up->Save(stream);

    //flag = m_right_back_up.get() != 0;
    //stream.write((char*)&flag, sizeof(flag));
    //if (flag)
    //	m_right_back_up->Save(stream);

    flag = m_right_back_down.get() != 0;
    stream.write((char*)&flag, sizeof(flag));
    if (flag)
        m_right_back_down->Save(stream);

    flag = m_left_front_up.get() != 0;
    stream.write((char*)&flag, sizeof(flag));
    if (flag)
        m_left_front_up->Save(stream);

    flag = m_left_front_down.get() != 0;
    stream.write((char*)&flag, sizeof(flag));
    if (flag)
        m_left_front_down->Save(stream);

    flag = m_left_back_up.get() != 0;
    stream.write((char*)&flag, sizeof(flag));
    if (flag)
        m_left_back_up->Save(stream);

    flag = m_left_back_down.get() != 0;
    stream.write((char*)&flag, sizeof(flag));
    if (flag)
        m_left_back_down->Save(stream);

    return true;
}

bool OctTree::Load(std::istream& stream)
{
    stream.read((char*)&m_cur_depth, sizeof(m_cur_depth));
    m_bbox.Load(stream);
    stream.read((char*)&m_is_finale, sizeof(m_is_finale));
    stream.read((char*)&m_face_count, sizeof(m_face_count));
    int has_data = 0;
    stream.read((char*)&has_data, sizeof(has_data));
    if (m_face_count && has_data)
    {
        m_face_list.resize(m_face_count);
        stream.read((char*)&m_face_list[0], sizeof(ivec3)*m_face_count);
    }

    if (m_is_finale)
        return true;

    int flag = m_right_front_up.get() != 0;
    stream.read((char*)&flag, sizeof(flag));
    if (flag)
    {
        m_right_front_up.reset(new OctTree);
        m_right_front_up->m_parent = this;
        m_right_front_up->Load(stream);
    }

    flag = m_right_front_down.get() != 0;
    stream.read((char*)&flag, sizeof(flag));
    if (flag)
    {
        m_right_front_down.reset(new OctTree);
        m_right_front_down->m_parent = this;
        m_right_front_down->Load(stream);
    }

    flag = m_right_back_up.get() != 0;
    stream.read((char*)&flag, sizeof(flag));
    if (flag)
    {
        m_right_back_up.reset(new OctTree);
        m_right_back_up->m_parent = this;
        m_right_back_up->Load(stream);
    }

    flag = 	m_right_back_down.get() != 0;
    stream.read((char*)&flag, sizeof(flag));
    if (flag)
    {
        m_right_back_down.reset(new OctTree);
        m_right_back_down->m_parent = this;
        m_right_back_down->Load(stream);
    }

    flag = 	m_left_front_up.get() != 0;
    stream.read((char*)&flag, sizeof(flag));
    if (flag)
    {
        m_left_front_up.reset(new OctTree);
        m_left_front_up->m_parent = this;
        m_left_front_up->Load(stream);
    }

    flag = 	m_left_front_down.get() != 0;
    stream.read((char*)&flag, sizeof(flag));
    if (flag)
    {
        m_left_front_down.reset(new OctTree);
        m_left_front_down->m_parent = this;
        m_left_front_down->Load(stream);
    }

    flag = 	m_left_back_up.get() != 0;
    stream.read((char*)&flag, sizeof(flag));
    if (flag)
    {
        m_left_back_up.reset(new OctTree);
        m_left_back_up->m_parent = this;
        m_left_back_up->Load(stream);
    }

    flag = 	m_left_back_down.get() != 0;
    stream.read((char*)&flag, sizeof(flag));
    if (flag)
    {
        m_left_back_down.reset(new OctTree);
        m_left_back_down->m_parent = this;
        m_left_back_down->Load(stream);
    }

    return true;
}
}
