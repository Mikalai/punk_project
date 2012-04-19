#ifndef _H_PUNK_UTILITY_OBJECT
#define _H_PUNK_UTILITY_OBJECT

#include <memory>
#include "mesh.h"
#include "../../math/mat4.h"

namespace Utility
{
	struct Object
	{
		System::string m_name;
		Math::BoundingBox m_bbox;
		std::auto_ptr<Mesh> m_mesh;
		Math::mat4 m_local_matrix;
		Math::mat4 m_world_matrix;
		Math::vec3 m_location;
		Math::OctTree m_oct_tree;

		bool IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, IntersectionCollection& res) const
		{
			Math::OctTree::FaceList fl  = m_oct_tree.CrossAll(Math::Line3D(start, end));
			if (fl.empty())
				return false;

			for (int tr = 0; tr < fl.size(); tr++)
			{
				const Math::vec3& a = m_mesh->m_vertices[fl[tr].X()];
				const Math::vec3& b = m_mesh->m_vertices[fl[tr].Y()];
				const Math::vec3& c = m_mesh->m_vertices[fl[tr].Z()];

				Math::Triangle3D triangle(a, b, c);
				Math::Line3D line(start, end);
				float t;
				if (Math::LineCrossTriangle(line, triangle, t) == Math::SKEW_CROSS)
				{
					res[m_name].push_back(line.PointAt(t));				
				}
			}			

			if (res.find(m_name) == res.end())
			{
				return false;
			}
			else
			{
				res[m_name].SetName(m_name);
				return true;
			}
		}
	};
}

#endif