#include "oct_tree.h"
#include "bounding_box.h"
#include "line3d.h"

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

		m_face_list.reserve(fl.size());
		FaceList::const_iterator end = fl.end();
		for (FaceList::const_iterator i = fl.begin(); i != end; ++i)
		{
			const ivec3& face = *i;
			const vec3& p1 = vertexList[face.X()];
			const vec3& p2 = vertexList[face.Y()];
			const vec3& p3 = vertexList[face.Z()];

			if (m_bbox.DoCrossTriangle(p1, p2, p3))
			{				
				m_face_list.push_back(face);
				++m_face_count;
			}
		}

		if (m_parent == 0 || m_face_count > MaxFaceCount && m_face_count != m_parent->m_face_count)
		{
			const vec3& min = m_bbox.Min();
			const vec3& max = m_bbox.Max();
			const vec3 mid = (min + max) / 2.0f;
			m_right_front_up.reset(new OctTree(this));
			m_right_front_up->m_bbox.Min() = vec3(mid.X(), mid.Y(), mid.Z());
			m_right_front_up->m_bbox.Max() = vec3(max.X(), max.Y(), max.Z());
			m_right_front_up->Build(m_face_list, vertexList);

			m_right_front_down.reset(new OctTree(this));
			m_right_front_down->m_bbox.Min() = vec3(mid.X(), mid.Y(), min.Z());
			m_right_front_down->m_bbox.Max() = vec3(max.X(), max.Y(), mid.Z());
			m_right_front_down->Build(m_face_list, vertexList);

			m_left_front_up.reset(new OctTree(this));
			m_left_front_up->m_bbox.Min() = vec3(min.X(), mid.Y(), mid.Z());
			m_left_front_up->m_bbox.Max() = vec3(mid.X(), max.Y(), max.Z());
			m_left_front_up->Build(m_face_list,vertexList);

			m_left_front_down.reset(new OctTree(this));
			m_left_front_down->m_bbox.Min() = vec3(min.X(), mid.Y(), min.Z());
			m_left_front_down->m_bbox.Max() = vec3(mid.X(), max.Y(), mid.Z());
			m_left_front_down->Build(m_face_list,vertexList);
			///////////////////////////////////////////////

			m_right_back_up.reset(new OctTree(this));
			m_right_back_up->m_bbox.Min() = vec3(mid.X(), min.Y(), mid.Z());
			m_right_back_up->m_bbox.Max() = vec3(max.X(), mid.Y(), max.Z());
			m_right_back_up->Build(m_face_list,vertexList);

			m_right_back_down.reset(new OctTree(this));
			m_right_back_down->m_bbox.Min() = vec3(mid.X(), min.Y(), min.Z());
			m_right_back_down->m_bbox.Max() = vec3(max.X(), mid.Y(), mid.Z());
			m_right_back_down->Build(m_face_list,vertexList);

			m_left_back_up.reset(new OctTree(this));
			m_left_back_up->m_bbox.Min() = vec3(min.X(), min.Y(), mid.Z());
			m_left_back_up->m_bbox.Max() = vec3(mid.X(), mid.Y(), max.Z());
			m_left_back_up->Build(m_face_list,vertexList);

			m_left_back_down.reset(new OctTree(this));
			m_left_back_down->m_bbox.Min() = vec3(min.X(), min.Y(), min.Z());
			m_left_back_down->m_bbox.Max() = vec3(mid.X(), mid.Y(), mid.Z());
			m_left_back_down->Build(m_face_list, vertexList);
		}
		else
		{
			m_is_finale = true;
		}
		return this;
	}

	OctTree::FaceList OctTree::Cross(const Line3D& line)
	{
		return CrossAll(line);
	}

	OctTree::FaceList OctTree::CrossAll(const Line3D& line)
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
}
